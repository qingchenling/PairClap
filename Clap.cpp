#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <windows.h>
#include <io.h>
using namespace std;

const int TIMES = 32; // 总测试次数
const int THREADS = 1; // 进程数

thread task[THREADS];
float bf=0,ans=0;
float bfmax,ansmax;
int num;
mutex mut;

void color(int a);
PCWSTR toPCWSTR(const char *str);
PCWSTR toPCWSTR(string str);
void work(string s, int t);

int main()
{
    SetConsoleOutputCP(65001);
    int eachTimes=TIMES/THREADS;

    puts("编译中...");
    if(access("tmp", 0)==-1) mkdir("tmp");
    system("g++ Data.cpp -std=c++11 -Wl,--stack=2147483647 -O2 -o tmp/Data.exe");
    system("g++ Std.cpp -std=c++11 -Wl,--stack=2147483647 -O2 -o tmp/Std.exe");
    system("g++ BF.cpp -std=c++11 -Wl,--stack=2147483647 -O2 -o tmp/BF.exe");

    for(int i=0; i<THREADS; i++)
    {
        char tmp[10];
        sprintf(tmp, "%d", i+1);
        string src="tmp\\Thread"; src=src+tmp+"\\";

        if(access(src.data(), 0)==-1) mkdir(src.data());
        CopyFile2(toPCWSTR("tmp/Data.exe"), toPCWSTR(src+"Data.exe"), 0);
        CopyFile2(toPCWSTR("tmp/Std.exe"), toPCWSTR(src+"Std.exe"), 0);
        CopyFile2(toPCWSTR("tmp/BF.exe"), toPCWSTR(src+"BF.exe"), 0);

        int q=(i==THREADS-1 ? TIMES-eachTimes*(THREADS-1) : eachTimes);
        task[i]=thread(work, src, q);
    }
    
    for(auto& th : task)
    th.join();

    printf("暴力平均时间: %.3f, 最长时间: %.3f\n", bf/TIMES, bfmax);
    printf("正解平均时间: %.3f, 最长时间: %.3f\n", ans/TIMES, ansmax);
    system("rmdir /S /Q tmp");
    return 0;
}

void color(int a) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a); }

PCWSTR toPCWSTR(const char *str)
{
	WCHAR *res = new WCHAR[256];
	MultiByteToWideChar(CP_ACP, 0, str,strlen(str)+1, res, 256);
	return res;
}

PCWSTR toPCWSTR(string str) { return toPCWSTR(str.data()); }

void work(string s, int t)
{
    int a,b,c;

    string DATA=s+"Data.exe", BF=s+"BF.exe", STD=s+"Std.exe";
    string In=s+"in.txt",OUT1=s+"bf.txt",OUT2=s+"ans.txt";
    string ord1=DATA+" >"+In;
    string ord2=BF+" <"+In+" >"+OUT1;
    string ord3=STD+" <"+In+" >"+OUT2;
    string ord4=string("fc ")+OUT1+" "+OUT2+" >nul";
    for(int i=1; i<=t; i++)
    {
        system(ord1.data()); a=clock();
        system(ord2.data()); b=clock();
        system(ord3.data()); c=clock();
        
        mut.lock();
        printf("Case %d:\n", ++num);
        if(system(ord4.data())!=0)
        {
            color(4);
            cerr<<"对比差异\n";
            CopyFile2(toPCWSTR(In), toPCWSTR("data.txt"), 0);
            CopyFile2(toPCWSTR(OUT1), toPCWSTR("bf.txt"), 0);
            CopyFile2(toPCWSTR(OUT2), toPCWSTR("ans.txt"), 0);
            system("rmdir /S /Q tmp");
            color(7);
            exit(0);
        }
        color(2); puts("无差异"); color(7);
        printf("朴素用时: %.3f秒\n", (float)(b-a)/1000);
        bf+=(float)(b-a)/1000;
        bfmax=max(bfmax, (float)(b-a)/1000);
        printf("正解用时: %.3f秒\n", (float)(c-b)/1000);
        ans+=(float)(c-b)/1000;
        ansmax=max(ansmax, (float)(c-b)/1000);
        puts("*******************************");
        mut.unlock();
    }
}