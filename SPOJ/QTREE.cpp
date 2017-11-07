#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int>pii;
const int MAXN = 100004;
struct edge {
    int des,dis,id;
    edge(int a,int b,int c) {
        tie(des,dis,id)=make_tuple(a,b,c);
    }
};
int N, T, cnt, top[MAXN], cst[MAXN], par[MAXN], depth[MAXN], heavy[MAXN], sz[MAXN], ei[MAXN], id[MAXN], st[MAXN<<1];
pii E[MAXN];
char S[16];
vector<edge>adj[MAXN];
void update(int pos,int val) {
    for(st[pos+=N]=val;pos>1;pos>>=1) st[pos>>1]=max(st[pos],st[pos^1]);
}
int query(int l, int r) {
    int res=0;
    for(l+=N,r+=N;l<r;l>>=1,r>>=1) {
        if(l&1) res=max(res,st[l++]);
        if(r&1) res=max(res,st[--r]);
    }
    return res;
}
void dfs1(int src, int p=0, int d=1) {
    sz[src]=1;
    par[src]=p;
    depth[src]=d;
    for(edge &e:adj[src])
        if(e.des^p) {
            dfs1(e.des, src, d+1);
            sz[src]+=sz[e.des];
            cst[e.des]=e.dis;
            ei[e.des]=e.id;
            if(!~heavy[src]||sz[e.des]>sz[heavy[src]])
                heavy[src]=e.des;
        }
}
void dfs2(int src, int par=0, int t=0) {
    id[ei[src]]=++cnt;
    update(id[ei[src]],cst[src]);
    top[src]=t;
    if(~heavy[src])
        dfs2(heavy[src],src,t);
    for(edge &e:adj[src])
        if(e.des^heavy[src]&&e.des^par)
            dfs2(e.des,src,e.des);
}
int main() {
    for(scanf("%d", &T);T--;) {
        scanf("%d", &N);
        for(int i=1;i<=N;++i)
            adj[i].clear();
        for(int i=1, a, b, c;i<N;i++) {
            scanf("%d%d%d", &a, &b, &c);
            adj[a].emplace_back(b, c, i);
            adj[b].emplace_back(a, c, i);
        }
        cnt=0;
        memset(heavy,-1,sizeof heavy);
        memset(st,0,sizeof st);
        dfs1(1);
        dfs2(1);
        do {
            scanf("%s",S);
            int a,b,res=0;
            if(S[0]=='Q') {
                scanf("%d%d",&a,&b);
                while(top[a]^top[b]) {
                    if(depth[par[top[a]]]<depth[par[top[b]]]) swap(a,b);
                    res=max(res,query(id[ei[top[a]]],id[ei[a]]+1));
                    a=par[top[a]];
                }
                if(depth[a]<depth[b]) swap(a,b);
                res=max(res,query(id[ei[b]]+1,id[ei[a]]+1));
                printf("%d\n",res);
            } else if(S[0]=='C') {
                scanf("%d%d",&a,&b);
                update(id[a],b);
            }
        }while(S[0]^'D');
    }
}
