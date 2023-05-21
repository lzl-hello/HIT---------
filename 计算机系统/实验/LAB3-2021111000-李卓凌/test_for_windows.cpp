#include<iostream>
#include<math.h>
#include<time.h>
using namespace std;

//要求是1920*1080 但是考虑到边缘元素的特殊性，在这里将数组扩大到1922*1082 
long image[1922][1082];
const int T = 100;//迭代100次 

void optimize_common0(){
	for(int j=1;j<1081;j++){
		//从第一列到第1080列，不考虑额外补充的两列
		for(int i=1;i<1921;i++){
			//从第一行到1920行，同上
			image[i][j] = (image[i-1][j] + image[i+1][j] + image[i][j-1] + image[i][j+1])/4;
		} 
	} 
}
void optimize_common1()
{
    for(int j = 1; j < 1081; j++)
    {
        for (int i = 1; i < 1921;i++)
        {
            image[i][j] = (image[i-1][j] + image[i+1][j]+image[i][j-1] + image[i][j+1] ) >> 2;
        }
    }
}

void optimize_cache0()
{
    for(int i = 1; i < 1921;i++)
    {
        for (int j = 1; j < 1081; j++)
        {
            image[i][j] = (image[i-1][j] + image[i+1][j]+image[i][j-1] + image[i][j+1] ) >> 2;
        }
    }
}

int minn(int a, int b) {
	return (a < b)? a: b; 
}
void optimize_cache1() {
	int i0, j0, i, j;
	int K = 8;
	//枚举每个8*8的小块
	for(i0 = 1; i0 < 1921; i0 += K) {
		for(j0 = 1; j0 < 1081; j0 += K) {
			//minn即min
			//boundi,boundj即块内的每个元素
			int boundi = minn(1921, i0 + K);
			int boundj = minn(1081, j0 + K);
			for(i = i0; i < boundi; i++) {
				for(j = j0; j < boundj; j++) {
					image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i - 1][j] + image[i + 1][j]) >> 2;
				}
			}
		}
	}
}
void optimize_cpu() {
	int i0, j0, i, j;
	int K = 8;
	//枚举每个8*8的小块
	for(i0 = 1; i0 < 1921; i0 += K) {
		for(j0 = 1; j0 < 1081; j0 += K) {
			//minn即min
			//boundi,boundj即块内的每个元素
			int boundi = minn(1921, i0 + K);
			int boundj = minn(1081, j0 + K);
			for(i = i0; i < boundi; i++) {
				for(j = j0; j < boundj-3; j+=4) {
//					image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i - 1][j] + image[i + 1][j]) / 4;
					image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i - 1][j] + image[i + 1][j]) >> 2;
					image[i][j + 1] = (image[i][j] + image[i][j + 2] + image[i - 1][j + 1] + image[i + 1][j + 1]) >> 2;
					image[i][j + 2] = (image[i][j + 1] + image[i][j + 3] + image[i - 1][j + 2] + image[i + 1][j + 2]) >> 2;
					image[i][j + 3] = (image[i][j + 2] + image[i][j + 4] + image[i - 1][j + 3] + image[i + 1][j + 3]) >> 2;
				}
				for(; j < boundj; j++) {
					image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i - 1][j] + image[i + 1][j]) >> 2;
				}
			}
		}
	}
}

//初始化数组，从零开始按行列递增，考虑到增加的两行和两列的实际数据对性能测试没有影响，故统一初始化即可 
void initialize(){
	for(int i=0;i<1922;i++){
		for(int j=0;j<1082;j++){
			image[i][j] = i+j;
		}
	}
}
//利用C标准库中的clock()函数进行测算
void testfunc(void (*optimize)()) {
	initialize();
	clock_t t1 = clock();
	int t = T;
	while(t--) {
		optimize();
	}
	clock_t t2 = clock();
	printf("time cost: %d(ms)\n",(t2 - t1) * 1000 / CLOCKS_PER_SEC);//保证各平台的一致性
}

int main(){
	cout<<"原始程序测试时间："; 
	testfunc(optimize_common0);
	cout<<"一般的程序优化测试时间："; 
	testfunc(optimize_common1);
	cout<<"面向cache0优化测试时间：";
	testfunc(optimize_cache0);
	cout<<"面向cache1优化测试时间：";
	testfunc(optimize_cache1);
	cout<<"面向cache+cpu优化测试时间：";
	testfunc(optimize_cpu);
	
	
} 

 
