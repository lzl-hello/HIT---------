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
	int K = 4;
	//枚举每个4*4的小块
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
	int K = 4;
	//枚举每个4*4的小块
	for(i0 = 1; i0 < 1921; i0 += K) {
		for(j0 = 1; j0 < 1081; j0 += K) {
			//minn即min
			//boundi,boundj即块内的每个元素
			int boundi = minn(1921, i0 + K);
			int boundj = minn(1081, j0 + K);
			for(i = i0; i < boundi; i++) {
				for(j = j0; j < boundj-95; j+=96) {
					int count[96] = {0};
					for(int k=0;k<96;k++){
						count[k] = j+k;
					} 
//					image[i][j] = (image[i][j - 1] + image[i][j + 1] + image[i - 1][j] + image[i + 1][j]) >> 2;
//					image[i][j + 1] = (image[i][j] + image[i][j + 2] + image[i - 1][j + 1] + image[i + 1][j + 1]) >> 2;
//					image[i][j + 2] = (image[i][j + 1] + image[i][j + 3] + image[i - 1][j + 2] + image[i + 1][j + 2]) >> 2;
//					image[i][j + 3] = (image[i][j + 2] + image[i][j + 4] + image[i - 1][j + 3] + image[i + 1][j + 3]) >> 2;
					image[i][count[0]] = (image[i][count[0]-1] + image[i][count[0]+ 1] + image[i - 1][count[0]] + image[i + 1][count[0]]) >> 2;
					image[i][count[1]] = (image[i][count[1]-1] + image[i][count[1]+ 1] + image[i - 1][count[1]] + image[i + 1][count[1]]) >> 2;
					image[i][count[2]] = (image[i][count[2]-1] + image[i][count[2]+ 1] + image[i - 1][count[2]] + image[i + 1][count[2]]) >> 2;
					image[i][count[3]] = (image[i][count[3]-1] + image[i][count[3]+ 1] + image[i - 1][count[3]] + image[i + 1][count[3]]) >> 2;
					image[i][count[4]] = (image[i][count[4]-1] + image[i][count[4]+ 1] + image[i - 1][count[4]] + image[i + 1][count[4]]) >> 2;
					image[i][count[5]] = (image[i][count[5]-1] + image[i][count[5]+ 1] + image[i - 1][count[5]] + image[i + 1][count[5]]) >> 2;
					image[i][count[6]] = (image[i][count[6]-1] + image[i][count[6]+ 1] + image[i - 1][count[6]] + image[i + 1][count[6]]) >> 2;
					image[i][count[7]] = (image[i][count[7]-1] + image[i][count[7]+ 1] + image[i - 1][count[7]] + image[i + 1][count[7]]) >> 2;
					image[i][count[8]] = (image[i][count[8]-1] + image[i][count[8]+ 1] + image[i - 1][count[8]] + image[i + 1][count[8]]) >> 2;
					image[i][count[9]] = (image[i][count[9]-1] + image[i][count[9]+ 1] + image[i - 1][count[9]] + image[i + 1][count[9]]) >> 2;
					image[i][count[10]] = (image[i][count[10]-1] + image[i][count[10]+ 1] + image[i - 1][count[10]] + image[i + 1][count[10]]) >> 2;
					image[i][count[11]] = (image[i][count[11]-1] + image[i][count[11]+ 1] + image[i - 1][count[11]] + image[i + 1][count[11]]) >> 2;
					image[i][count[12]] = (image[i][count[12]-1] + image[i][count[12]+ 1] + image[i - 1][count[12]] + image[i + 1][count[12]]) >> 2;
					image[i][count[13]] = (image[i][count[13]-1] + image[i][count[13]+ 1] + image[i - 1][count[13]] + image[i + 1][count[13]]) >> 2;
					image[i][count[14]] = (image[i][count[14]-1] + image[i][count[14]+ 1] + image[i - 1][count[14]] + image[i + 1][count[14]]) >> 2;
					image[i][count[15]] = (image[i][count[15]-1] + image[i][count[15]+ 1] + image[i - 1][count[15]] + image[i + 1][count[15]]) >> 2; 
					image[i][count[16]] = (image[i][count[16]-1] + image[i][count[16]+ 1] + image[i - 1][count[16]] + image[i + 1][count[16]]) >> 2;
					image[i][count[17]] = (image[i][count[17]-1] + image[i][count[17]+ 1] + image[i - 1][count[17]] + image[i + 1][count[17]]) >> 2;
					image[i][count[18]] = (image[i][count[18]-1] + image[i][count[18]+ 1] + image[i - 1][count[18]] + image[i + 1][count[18]]) >> 2;
					image[i][count[19]] = (image[i][count[19]-1] + image[i][count[19]+ 1] + image[i - 1][count[19]] + image[i + 1][count[19]]) >> 2;
					image[i][count[20]] = (image[i][count[20]-1] + image[i][count[20]+ 1] + image[i - 1][count[20]] + image[i + 1][count[20]]) >> 2;
					image[i][count[21]] = (image[i][count[21]-1] + image[i][count[21]+ 1] + image[i - 1][count[21]] + image[i + 1][count[21]]) >> 2;
					image[i][count[22]] = (image[i][count[22]-1] + image[i][count[22]+ 1] + image[i - 1][count[22]] + image[i + 1][count[22]]) >> 2;
					image[i][count[23]] = (image[i][count[23]-1] + image[i][count[23]+ 1] + image[i - 1][count[23]] + image[i + 1][count[23]]) >> 2;
					image[i][count[24]] = (image[i][count[24]-1] + image[i][count[24]+ 1] + image[i - 1][count[24]] + image[i + 1][count[24]]) >> 2;
					image[i][count[25]] = (image[i][count[25]-1] + image[i][count[25]+ 1] + image[i - 1][count[25]] + image[i + 1][count[25]]) >> 2;
					image[i][count[26]] = (image[i][count[26]-1] + image[i][count[26]+ 1] + image[i - 1][count[26]] + image[i + 1][count[26]]) >> 2;
					image[i][count[27]] = (image[i][count[27]-1] + image[i][count[27]+ 1] + image[i - 1][count[27]] + image[i + 1][count[27]]) >> 2;
					image[i][count[28]] = (image[i][count[28]-1] + image[i][count[28]+ 1] + image[i - 1][count[28]] + image[i + 1][count[28]]) >> 2;
					image[i][count[29]] = (image[i][count[29]-1] + image[i][count[29]+ 1] + image[i - 1][count[29]] + image[i + 1][count[29]]) >> 2;
					image[i][count[30]] = (image[i][count[30]-1] + image[i][count[30]+ 1] + image[i - 1][count[30]] + image[i + 1][count[30]]) >> 2;
					image[i][count[31]] = (image[i][count[31]-1] + image[i][count[31]+ 1] + image[i - 1][count[31]] + image[i + 1][count[31]]) >> 2;
					image[i][count[32]] = (image[i][count[32]-1] + image[i][count[32]+ 1] + image[i - 1][count[32]] + image[i + 1][count[32]]) >> 2;
					image[i][count[33]] = (image[i][count[33]-1] + image[i][count[33]+ 1] + image[i - 1][count[33]] + image[i + 1][count[33]]) >> 2;
					image[i][count[34]] = (image[i][count[34]-1] + image[i][count[34]+ 1] + image[i - 1][count[34]] + image[i + 1][count[34]]) >> 2;
					image[i][count[35]] = (image[i][count[35]-1] + image[i][count[35]+ 1] + image[i - 1][count[35]] + image[i + 1][count[35]]) >> 2;
					image[i][count[36]] = (image[i][count[36]-1] + image[i][count[36]+ 1] + image[i - 1][count[36]] + image[i + 1][count[36]]) >> 2;
					image[i][count[37]] = (image[i][count[37]-1] + image[i][count[37]+ 1] + image[i - 1][count[37]] + image[i + 1][count[37]]) >> 2;
					image[i][count[38]] = (image[i][count[38]-1] + image[i][count[38]+ 1] + image[i - 1][count[38]] + image[i + 1][count[38]]) >> 2;
					image[i][count[39]] = (image[i][count[39]-1] + image[i][count[39]+ 1] + image[i - 1][count[39]] + image[i + 1][count[39]]) >> 2;
					image[i][count[40]] = (image[i][count[40]-1] + image[i][count[40]+ 1] + image[i - 1][count[40]] + image[i + 1][count[40]]) >> 2;
					image[i][count[41]] = (image[i][count[41]-1] + image[i][count[41]+ 1] + image[i - 1][count[41]] + image[i + 1][count[41]]) >> 2;
					image[i][count[42]] = (image[i][count[42]-1] + image[i][count[42]+ 1] + image[i - 1][count[42]] + image[i + 1][count[42]]) >> 2;
					image[i][count[43]] = (image[i][count[43]-1] + image[i][count[43]+ 1] + image[i - 1][count[43]] + image[i + 1][count[43]]) >> 2;
					image[i][count[44]] = (image[i][count[44]-1] + image[i][count[44]+ 1] + image[i - 1][count[44]] + image[i + 1][count[44]]) >> 2;
					image[i][count[45]] = (image[i][count[45]-1] + image[i][count[45]+ 1] + image[i - 1][count[45]] + image[i + 1][count[45]]) >> 2;
					image[i][count[46]] = (image[i][count[46]-1] + image[i][count[46]+ 1] + image[i - 1][count[46]] + image[i + 1][count[46]]) >> 2;
					image[i][count[47]] = (image[i][count[47]-1] + image[i][count[47]+ 1] + image[i - 1][count[47]] + image[i + 1][count[47]]) >> 2;
					image[i][count[48]] = (image[i][count[48]-1] + image[i][count[48]+ 1] + image[i - 1][count[48]] + image[i + 1][count[48]]) >> 2;
					image[i][count[49]] = (image[i][count[49]-1] + image[i][count[49]+ 1] + image[i - 1][count[49]] + image[i + 1][count[49]]) >> 2;
					image[i][count[50]] = (image[i][count[50]-1] + image[i][count[50]+ 1] + image[i - 1][count[50]] + image[i + 1][count[50]]) >> 2;
					image[i][count[51]] = (image[i][count[51]-1] + image[i][count[51]+ 1] + image[i - 1][count[51]] + image[i + 1][count[51]]) >> 2;
					image[i][count[52]] = (image[i][count[52]-1] + image[i][count[52]+ 1] + image[i - 1][count[52]] + image[i + 1][count[52]]) >> 2;
					image[i][count[53]] = (image[i][count[53]-1] + image[i][count[53]+ 1] + image[i - 1][count[53]] + image[i + 1][count[53]]) >> 2;
					image[i][count[54]] = (image[i][count[54]-1] + image[i][count[54]+ 1] + image[i - 1][count[54]] + image[i + 1][count[54]]) >> 2;
					image[i][count[55]] = (image[i][count[55]-1] + image[i][count[55]+ 1] + image[i - 1][count[55]] + image[i + 1][count[55]]) >> 2;
					image[i][count[56]] = (image[i][count[56]-1] + image[i][count[56]+ 1] + image[i - 1][count[56]] + image[i + 1][count[56]]) >> 2;
					image[i][count[57]] = (image[i][count[57]-1] + image[i][count[57]+ 1] + image[i - 1][count[57]] + image[i + 1][count[57]]) >> 2;
					image[i][count[58]] = (image[i][count[58]-1] + image[i][count[58]+ 1] + image[i - 1][count[58]] + image[i + 1][count[58]]) >> 2;
					image[i][count[59]] = (image[i][count[59]-1] + image[i][count[59]+ 1] + image[i - 1][count[59]] + image[i + 1][count[59]]) >> 2;
					image[i][count[60]] = (image[i][count[60]-1] + image[i][count[60]+ 1] + image[i - 1][count[60]] + image[i + 1][count[60]]) >> 2;
					image[i][count[61]] = (image[i][count[61]-1] + image[i][count[61]+ 1] + image[i - 1][count[61]] + image[i + 1][count[61]]) >> 2;
					image[i][count[62]] = (image[i][count[62]-1] + image[i][count[62]+ 1] + image[i - 1][count[62]] + image[i + 1][count[62]]) >> 2;
					image[i][count[63]] = (image[i][count[63]-1] + image[i][count[63]+ 1] + image[i - 1][count[63]] + image[i + 1][count[63]]) >> 2;
					image[i][count[64]] = (image[i][count[64]-1] + image[i][count[64]+ 1] + image[i - 1][count[64]] + image[i + 1][count[64]]) >> 2;
					image[i][count[65]] = (image[i][count[65]-1] + image[i][count[65]+ 1] + image[i - 1][count[65]] + image[i + 1][count[65]]) >> 2;
					image[i][count[66]] = (image[i][count[66]-1] + image[i][count[66]+ 1] + image[i - 1][count[66]] + image[i + 1][count[66]]) >> 2;
					image[i][count[67]] = (image[i][count[67]-1] + image[i][count[67]+ 1] + image[i - 1][count[67]] + image[i + 1][count[67]]) >> 2;
					image[i][count[68]] = (image[i][count[68]-1] + image[i][count[68]+ 1] + image[i - 1][count[68]] + image[i + 1][count[68]]) >> 2;
					image[i][count[69]] = (image[i][count[69]-1] + image[i][count[69]+ 1] + image[i - 1][count[69]] + image[i + 1][count[69]]) >> 2;
					image[i][count[70]] = (image[i][count[70]-1] + image[i][count[70]+ 1] + image[i - 1][count[70]] + image[i + 1][count[70]]) >> 2;
					image[i][count[71]] = (image[i][count[71]-1] + image[i][count[71]+ 1] + image[i - 1][count[71]] + image[i + 1][count[71]]) >> 2;
					image[i][count[72]] = (image[i][count[72]-1] + image[i][count[72]+ 1] + image[i - 1][count[72]] + image[i + 1][count[72]]) >> 2;
					image[i][count[73]] = (image[i][count[73]-1] + image[i][count[73]+ 1] + image[i - 1][count[73]] + image[i + 1][count[73]]) >> 2;
					image[i][count[74]] = (image[i][count[74]-1] + image[i][count[74]+ 1] + image[i - 1][count[74]] + image[i + 1][count[74]]) >> 2;
					image[i][count[75]] = (image[i][count[75]-1] + image[i][count[75]+ 1] + image[i - 1][count[75]] + image[i + 1][count[75]]) >> 2;
					image[i][count[76]] = (image[i][count[76]-1] + image[i][count[76]+ 1] + image[i - 1][count[76]] + image[i + 1][count[76]]) >> 2;
					image[i][count[77]] = (image[i][count[77]-1] + image[i][count[77]+ 1] + image[i - 1][count[77]] + image[i + 1][count[77]]) >> 2;
					image[i][count[78]] = (image[i][count[78]-1] + image[i][count[78]+ 1] + image[i - 1][count[78]] + image[i + 1][count[78]]) >> 2;
					image[i][count[79]] = (image[i][count[79]-1] + image[i][count[79]+ 1] + image[i - 1][count[79]] + image[i + 1][count[79]]) >> 2;
					image[i][count[80]] = (image[i][count[80]-1] + image[i][count[80]+ 1] + image[i - 1][count[80]] + image[i + 1][count[80]]) >> 2;
					image[i][count[81]] = (image[i][count[81]-1] + image[i][count[81]+ 1] + image[i - 1][count[81]] + image[i + 1][count[81]]) >> 2;
					image[i][count[82]] = (image[i][count[82]-1] + image[i][count[82]+ 1] + image[i - 1][count[82]] + image[i + 1][count[82]]) >> 2;
					image[i][count[83]] = (image[i][count[83]-1] + image[i][count[83]+ 1] + image[i - 1][count[83]] + image[i + 1][count[83]]) >> 2;
					image[i][count[84]] = (image[i][count[84]-1] + image[i][count[84]+ 1] + image[i - 1][count[84]] + image[i + 1][count[84]]) >> 2;
					image[i][count[85]] = (image[i][count[85]-1] + image[i][count[85]+ 1] + image[i - 1][count[85]] + image[i + 1][count[85]]) >> 2;
					image[i][count[86]] = (image[i][count[86]-1] + image[i][count[86]+ 1] + image[i - 1][count[86]] + image[i + 1][count[86]]) >> 2;
					image[i][count[87]] = (image[i][count[87]-1] + image[i][count[87]+ 1] + image[i - 1][count[87]] + image[i + 1][count[87]]) >> 2;
					image[i][count[88]] = (image[i][count[88]-1] + image[i][count[88]+ 1] + image[i - 1][count[88]] + image[i + 1][count[88]]) >> 2;
					image[i][count[89]] = (image[i][count[89]-1] + image[i][count[89]+ 1] + image[i - 1][count[89]] + image[i + 1][count[89]]) >> 2;
					image[i][count[90]] = (image[i][count[90]-1] + image[i][count[90]+ 1] + image[i - 1][count[90]] + image[i + 1][count[90]]) >> 2;
					image[i][count[91]] = (image[i][count[91]-1] + image[i][count[91]+ 1] + image[i - 1][count[91]] + image[i + 1][count[91]]) >> 2;
					image[i][count[92]] = (image[i][count[92]-1] + image[i][count[92]+ 1] + image[i - 1][count[92]] + image[i + 1][count[92]]) >> 2;
					image[i][count[93]] = (image[i][count[93]-1] + image[i][count[93]+ 1] + image[i - 1][count[93]] + image[i + 1][count[93]]) >> 2;
					image[i][count[94]] = (image[i][count[94]-1] + image[i][count[94]+ 1] + image[i - 1][count[94]] + image[i + 1][count[94]]) >> 2;
					image[i][count[95]] = (image[i][count[95]-1] + image[i][count[95]+ 1] + image[i - 1][count[95]] + image[i + 1][count[95]]) >> 2;
					
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

 
