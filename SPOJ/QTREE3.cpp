#include<bits/stdc++.h>
#include<bits/extc++.h>
typedef std::pair<int,int> pii;
const int MAXN=1e5+4;
int N,Q,heavy[MAXN],par[MAXN],top[MAXN],sz[MAXN],depth[MAXN];
std::vector<int>adj[MAXN];
std::unordered_map<int,std::set<pii>>M;
void dfs1(int src,int p,int d=0) {
    par[src]=p;
    sz[src]=1;
    depth[src]=d;
    for(int i:adj[src]) {
        if(i==p) continue;
        dfs1(i,src,d+1);
        sz[src]+=sz[i];
        if(!~heavy[src]||sz[i]>sz[heavy[src]])
            heavy[src]=i;
    }
}
void dfs2(int src,int p,int t) {
    top[src]=t;
    if(~heavy[src]) dfs2(heavy[src],src,t);
    for(int i:adj[src]) {
        if(i==p||i==heavy[src]) continue;
        dfs2(i,src,i);
    }
}
inline void update(int src) {
    if(M[top[src]].count({depth[src],src}))
        M[top[src]].erase({depth[src],src});
    else
        M[top[src]].insert({depth[src],src});
}
inline int query(int src) {
    int ans=-1;
    while(~top[src]) {
        if(!M[top[src]].empty()) {
            pii tmp=*M[top[src]].begin();
            if(tmp.first<=depth[src])
                ans=tmp.second;
        }
        src=par[top[src]];
    }
    if(!M[-1].empty()) {
        pii tmp=*M[-1].begin();
        if(tmp.first<=depth[src])
            ans=tmp.second;
    }
    return ans;
}
int main() {
    scanf("%d%d",&N,&Q);
    for(int i=1,a,b;i<N;++i) {
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    memset(heavy,-1,sizeof heavy);
    dfs1(1,-1);
    dfs2(1,-1,-1);
    for(int i=0,a,b;i<Q;++i) {
        scanf("%d%d",&a,&b);
        if(a)
            printf("%d\n",query(b));
        else
            update(b);
    }
}
