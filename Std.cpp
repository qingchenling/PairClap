#include<bits/stdc++.h>
using namespace std;

struct trie01
{
    int tr[2000100][16];
    bool h[2000100][16];
    int flag[2000100];
    int cnt=1;
    void insert(int x)
    {
        int u=1;
        stack<int> s; s.push(u);
        for(int i=15; i>=0; i--)
        {
            int b=(x>>i)&1;
            if(!tr[u][b]) tr[u][b]=++cnt;
            u=tr[u][b]; s.push(u);
        }
        ++flag[u];
        while(s.size())
        {
            int u=s.top(); s.pop();
            for(int i=2; i<=15; i++)
            h[u][i]=h[tr[u][0]][i-1]||h[tr[u][1]][i-1];
            h[u][1]=(tr[u][1]!=0);
        }
    }
    void XOR(int x)
    {
        int u=1;
        int maxn=0;
        for(int i=15; i>=0; i--)
        {
            int b=(x>>i)&1;
            if(tr[u][!b]) maxn|=1<<i,u=tr[u][!b];
            else u=tr[u][b];
        }
        printf("%d %d\n", maxn, flag[u]);
    }
    void OR(int x)
    {
        int u=1;
        int maxn=0;
        for(int i=15,j; i>=0; i--)
        {
            int b=(x>>i)&1;
            if(!b&&tr[u][1]) u=tr[u][1],maxn|=1<<i;
            else if(!b) u=tr[u][0];
            else
            {
                if(!tr[u][1]||!tr[u][0]) u=tr[u][1]+tr[u][0];
                else
                {
                    for(j=1; j<=i; j++)
                    if(!((x>>i-j)&1)&&(h[tr[u][0]][j]^h[tr[u][1]][j]))
                    {
                        u=h[tr[u][0]][j] ? tr[u][0] : tr[u][1];
                        break;
                    }
                    if(j>15) u=tr[u][0];
                }
            }
        }
        printf("%d\n", maxn);
    }
    void AND(int x)
    {
        int u=1;
        int maxn=0;
        for(int i=15,j; i>=0; i--)
        {
            int b=(x>>i)&1;
            if(b&&tr[u][1]) u=tr[u][1],maxn|=1<<i;
            else if(b) u=tr[u][0];
            else
            {
                if(!tr[u][1]||!tr[u][0]) u=tr[u][1]+tr[u][0];
                else
                {
                    for(j=1; j<=i; j++)
                    if(((x>>i-j)&1)&&(h[tr[u][0]][j]^h[tr[u][1]][j]))
                    {
                        u=h[tr[u][0]][j] ? tr[u][0] : tr[u][1];
                        break;
                    }
                    if(j>15) u=tr[u][0];
                }
            }
        }
        printf("%d\n", maxn);
    }
};

trie01 t;
int a[100100];

int main()
{
    int n,type;
    char opt[5];
    int i;

    cin>>n>>opt>>type;
    for(i=1; i<=n; i++)
    scanf("%d", &a[i]);

    t.insert(a[1]);
    for(i=2; i<=n; i++)
    {
        switch(opt[0])
        {
        case 'a': t.AND(a[i]); break;
        case 'o': t.OR(a[i]); break;
        case 'x': t.XOR(a[i]); break;
        }
        t.insert(a[i]);
    }
    return 0;
}