#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int ___init=[](){
	srand(time(0));
	return 1;
}();

// Rand a Int
int randInt(int l, int r)
{
	return l+(1.0*rand()/RAND_MAX)*(r-l+1);
}

// Rand a long long
ll randll(ll l, ll r)
{
	return l+(1.0*rand()/RAND_MAX)*(r-l+1);
}

// Rand a array of [l,r] (Will output)
bool randArray(int n, int l, int r)
{
	for(int i=1; i<=n; i++)
	printf("%d ", randInt(l, r));
	putchar('\n');
	return 1;
}

/**
 * Rand a DAG
 * @param[in] self 是否自环
 * @param[in] same 是否重边
*/
bool randDAG(int n, int m, bool self, bool same)
{
	static map<pair<int,int>, bool> mp;
	for(int i=1; i<=m; i++)
	{
		int x,y;
		do x=randInt(1, n),y=randInt(1, n);
		while((mp.count(make_pair(x, y))&&!same)||(x==y&&!self));
		printf("%d %d\n", x, y);
	}
	return 1;
}