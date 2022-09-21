#include<iostream>
#include<cstdio>
using namespace std;
const int SIZE=1e5+10;
int a[SIZE];

namespace Trie{

    int son[SIZE*20][2],siz[SIZE*20],postot;

    void insert(int x){

        int cur=0;
        for(int i=18;i>=0;i--)
        {
            siz[cur]++;
            int &p=son[cur][(x>>i)&1];
            if(!p) p=++postot;
            cur=p;
        }
        siz[cur]++;

    }

    int query_xor(int x){

        int cur=0;
        int ans=0;
        for(int i=18;i>=0;i--)
        {
            int flag=(x>>i)&1;
            if(son[cur][flag^1]) ans+=1<<i,cur=son[cur][flag^1];
            else cur=son[cur][flag];
        }
        return ans;

    }

}

namespace TaskAnd{

    void main(int n,int type){

        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            int ans1=0,ans2=0;
            for(int j=1;j<i;j++)
            {
                if((a[i]&a[j])>ans1)
                    ans1=a[i]&a[j],ans2=1;
                else if((a[i]&a[j])==ans1)
                    ans2++;
            }
            if(i>1)
            {
                if(!type) printf("%d\n",ans1);
                else printf("%d %d\n",ans1,ans2);
            }
        }
    }

}

namespace TaskOr{

    void main(int n,int type){

        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            int ans1=0,ans2=0;
            for(int j=1;j<i;j++)
            {
                if((a[i]|a[j])>ans1)
                    ans1=a[i]|a[j],ans2=1;
                else if((a[i]|a[j])==ans1)
                    ans2++;
            }
            if(i>1)
            {
                if(!type) printf("%d\n",ans1);
                else printf("%d %d\n",ans1,ans2);
            }
        }

    }

}

namespace TaskXor{

    int T[SIZE];
    void main(int n,int type){

        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            int ans1=Trie::query_xor(a[i]);
            int ans2=T[a[i]^ans1];
            if(i>1)
            {
                if(!type) printf("%d\n",ans1);
                else printf("%d %d\n",ans1,ans2);
            }
            T[a[i]]++;
            Trie::insert(a[i]);
        }

    }

}
int main(){
    int n;
    string s;
    int type;

    scanf("%d",&n);
    cin>>s;
    scanf("%d",&type);

    int op;
    if(s[0]=='a') op=0;
    else if(s[0]=='o') op=1;
    else if(s[0]=='x') op=2;

    if(op==0) TaskAnd::main(n,type);
    else if(op==1) TaskOr::main(n,type);
    else TaskXor::main(n,type);

    return 0;

}