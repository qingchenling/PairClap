#include<bits/stdc++.h>
using namespace std;

int randInt(int l,int r);

int main()
{
	srand(time(0));
	srand(rand());
	
	return 0;
}
int randInt(int l,int r)
{
	return l+(l+rand())%r;
}
