#include<iostream>
#include<math.h>
#include<time.h>
using namespace std;

//Ҫ����1920*1080 ���ǿ��ǵ���ԵԪ�ص������ԣ������ｫ��������1922*1082 
long image[1922][1082];
const int T = 100;//����100�� 

void optimize_common0(){
	for(int j=1;j<1081;j++){
		//�ӵ�һ�е���1080�У������Ƕ��ⲹ�������
		for(int i=1;i<1921;i++){
			//�ӵ�һ�е�1920�У�ͬ��
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
	//ö��ÿ��8*8��С��
	for(i0 = 1; i0 < 1921; i0 += K) {
		for(j0 = 1; j0 < 1081; j0 += K) {
			//minn��min
			//boundi,boundj�����ڵ�ÿ��Ԫ��
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
	//ö��ÿ��8*8��С��
	for(i0 = 1; i0 < 1921; i0 += K) {
		for(j0 = 1; j0 < 1081; j0 += K) {
			//minn��min
			//boundi,boundj�����ڵ�ÿ��Ԫ��
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

//��ʼ�����飬���㿪ʼ�����е��������ǵ����ӵ����к����е�ʵ�����ݶ����ܲ���û��Ӱ�죬��ͳһ��ʼ������ 
void initialize(){
	for(int i=0;i<1922;i++){
		for(int j=0;j<1082;j++){
			image[i][j] = i+j;
		}
	}
}
//����C��׼���е�clock()�������в���
void testfunc(void (*optimize)()) {
	initialize();
	clock_t t1 = clock();
	int t = T;
	while(t--) {
		optimize();
	}
	clock_t t2 = clock();
	printf("time cost: %d(ms)\n",(t2 - t1) * 1000 / CLOCKS_PER_SEC);//��֤��ƽ̨��һ����
}

int main(){
	cout<<"ԭʼ�������ʱ�䣺"; 
	testfunc(optimize_common0);
	cout<<"һ��ĳ����Ż�����ʱ�䣺"; 
	testfunc(optimize_common1);
	cout<<"����cache0�Ż�����ʱ�䣺";
	testfunc(optimize_cache0);
	cout<<"����cache1�Ż�����ʱ�䣺";
	testfunc(optimize_cache1);
	cout<<"����cache+cpu�Ż�����ʱ�䣺";
	testfunc(optimize_cpu);
	
	
} 

 
