#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int>pii;
typedef long long ll;
const int MAXN=1e4+4,MAXLN=15;
int N,T;
ll depth[MAXN],st[2][MAXN][MAXLN];
vector<pii>adj[MAXN];
char S[8];
void dfs(int src,int par,ll d=0) {
    depth[src]=d;
    st[0][src][0]=par;
    for(auto a:adj[src]) {
        if(a.first==par) continue;
        st[1][a.first][0]=a.second;
        dfs(a.first,src,d+1);
    }
}
void build() {
    for(int j=1;j<MAXLN;++j)
        for(int i=1;i<=N;++i)
            if(~st[0][i][j-1]) {
                st[0][i][j]=st[0][st[0][i][j-1]][j-1];
                st[1][i][j]=st[1][i][j-1]+st[1][st[0][i][j-1]][j-1];
            } else {
                st[0][i][j]=-1;
                st[1][i][j]=st[1][i][j-1];
            }
}
ll query(int a,int d) {
    ll res=0;
    for(int i=MAXLN-1;i>=0;--i)
        if(d&(1<<i)) {
        	res+=st[1][a][i];
            a=st[0][a][i];
        }
    return res;
}
ll lca(int a,int b) {
    if(depth[a]<depth[b]) swap(a,b);
    for(int i=MAXLN-1;i>=0;--i)
        if(~st[0][a][i]&&depth[st[0][a][i]]>=depth[b]) {
            a=st[0][a][i];
        }
    if(a==b) return a;
    for(int i=MAXLN-1;i>=0;--i)
        if(st[0][a][i]!=st[0][b][i]) {
            a=st[0][a][i];
            b=st[0][b][i];
        }
    return st[0][a][0];
}
ll find(int a,int d) {
    for(int i=MAXLN-1;i>=0;--i)
        if(d&(1<<i))
            a=st[0][a][i];
    return a;
}
int main() {
    for(scanf("%d",&T);T--;) {
    	scanf("%d",&N);
        memset(st,0,sizeof st);
        memset(depth,0,sizeof depth);
        for(int i=1;i<=N;adj[i++].clear());
        for(int i=1,a,b,c;i<N;++i) {
            scanf("%d%d%d",&a,&b,&c);
            adj[a].emplace_back(b,c);
            adj[b].emplace_back(a,c);
        }
        dfs(1,-1);
        build();
        do {
        	memset(S,0,sizeof S);
            scanf("%s",S);
            if(!strcmp(S,"DIST")) {
                int a,b;
                scanf("%d%d",&a,&b);
                ll l=lca(a,b);
                printf("%lld\n",query(a,depth[a]-depth[l])+query(b,depth[b]-depth[l]));
            } else if(!strcmp(S,"KTH")) {
                int a,b,c;
                scanf("%d%d%d",&a,&b,&c);
                ll l=lca(a,b);
                if(c<=depth[a]-depth[l]+1)
                    printf("%lld\n",find(a,c-1));
                else {
                    int td = depth[a]+depth[b]-2*depth[l]+1;
                    printf("%lld\n",find(b,td-c));
                }
            }
        }while(strcmp(S,"DONE"));
        puts("");
    }
}
