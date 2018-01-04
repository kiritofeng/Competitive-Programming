#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e5+4;
int N,C[MN],cnt[MN],hvy[MN],sz[MN],tcnt,tin[MN],tout[MN],tour[MN];
std::vector<int>adj[MN];
std::map<int,ll,std::greater<int>>M;
ll ans[MN];
void dfs1(int src,int par){
    tour[tin[src]=++tcnt]=src;
    sz[src]=1;
    hvy[src]=-1;
    for(int i:adj[src]){
        if(i==par) continue;
        dfs1(i,src);
        if(!~hvy[src]||sz[i]>sz[hvy[src]]) hvy[src]=i;
        sz[src]+=sz[i];
    }
    tout[src]=tcnt;
}
inline void upd(int c,int i){
    if(!(M[cnt[c]]-=c))
        M.erase(cnt[c]);
    M[cnt[c]+=i]+=c;
}
void dfs2(int src,int par,int keep=0){
    for(int i:adj[src]){
        if(i==par||i==hvy[src]) continue;
        dfs2(i,src);
    }
    if(~hvy[src]) dfs2(hvy[src],src,1);
    for(int i:adj[src]){
        if(i==par||i==hvy[src]) continue;
        for(int j=tin[i];j<=tout[i];++j)
            upd(C[tour[j]],1);
    }
    upd(C[src],1);
    ans[src]=M.begin()->second;
    if(!keep)
        for(int i=tin[src];i<=tout[src];++i)
            upd(C[tour[i]],-1);
}
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;scanf("%d",C+i++));
    for(int i=1,a,b;i<N;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    dfs1(1,1);
    dfs2(1,1);
    for(int i=1;i<=N;printf("%lld ",ans[i++]));
}
