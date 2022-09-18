#include<windows.h>
#include<iostream>
#include<ctime>
using namespace std;

const int TIMES = 50; // 测试次数

float bf=0,ans=0;
float bfmax,ansmax;
int a,b,c;

int main()
{
	for(int i=1;i<=TIMES;i++)
	{
		printf("Case %d:\n", i);
		
		system("数据.exe >in.txt"); a=clock();
		system("朴素算法.exe <in.txt >bf.txt"); b=clock();
		system("正解.exe <in.txt >ans.txt"); c=clock();
		if(system("fc bf.txt ans.txt")!=0)break;
		
		printf("朴素用时: %.3f秒\n", (float)(b-a)/1000);
		bf+=(float)(b-a)/1000;
		bfmax=max(bfmax, (float)(b-a)/1000);
		printf("正解用时: %.3f秒\n", (float)(c-b)/1000);
		ans+=(float)(c-b)/1000;
		ansmax=max(ansmax, (float)(b-a)/1000);
		cout<<"*******************************\n";
	}
	printf("暴力平均时间: %f, 最长时间: %f\n", bf/TIMES, bfmax);
	printf("正解平均时间: %f, 最长时间: %f\n", ans/TIMES, ansmax);
	return 0;
}
