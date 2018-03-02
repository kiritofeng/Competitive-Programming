#include<bits/stdc++.h>
const int MN=1e5+4;
int N,M,R,valcnt,ecnt,res,ein[MN],eout[MN],eid[MN],sz[MN],hvy[MN],cnt[MN],col[MN],vals[MN],ans[MN];
std::vector<int>adj[MN],qrys[MN];
inline void add(int i){
    if(!cnt[i]++) ++res;
}
inline void rem(int i){
    if(!--cnt[i]) --res;
}
void dfs1(int src,int par){
    eid[ein[src]=++ecnt]=src;
    sz[src]=1;
    hvy[src]=-1;
    for(int i:adj[src]){
        if(i==par)continue;
        dfs1(i,src);
        sz[src]+=sz[i];
        if(!~hvy[src]||sz[hvy[src]]<sz[i]) hvy[src]=i;
    }
    eout[src]=ecnt;
}
void dfs2(int src,int par,bool keep=0){
    for(int i:adj[src]){
        if(i==par||i==hvy[src]) continue;
        dfs2(i,src);
    }
    if(~hvy[src]) dfs2(hvy[src],src,1);
    for(int i:adj[src]){
        if(i==par||i==hvy[src]) continue;
        for(int j=ein[i];j<=eout[i];++j)
            add(col[eid[j]]);
    }
    add(col[src]);
    for(int i:qrys[src]) ans[i]=res;
    if(keep) return;
    for(int i=ein[src];i<=eout[src];++i)
        rem(col[eid[i]]);
}
int main(){
    scanf("%d%d%d",&N,&M,&R);
    for(int i=1,a,b;i<N;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    for(int i=1;i<=N;++i){
        scanf("%d",col+i);
        vals[i-1]=col[i];
    }
    std::sort(vals,vals+N);
    valcnt=std::unique(vals,vals+N)-vals;
    for(int i=1;i<=N;++i)
        col[i]=std::lower_bound(vals,vals+valcnt,col[i])-vals;
    for(int i=0,a;i<M;++i){
        scanf("%d",&a);
        qrys[a].emplace_back(i);
    }
    dfs1(R,-1);
    dfs2(R,-1);
    for(int i=0;i<M;printf("%d\n",ans[i++]));
}
