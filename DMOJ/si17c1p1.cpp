#include<bits/stdc++.h>
typedef std::pair<int,int> pii;
typedef long long ll;
const int MN=22,INF=0x3f3f3f3f;
int N,M,K,sz,dist[MN],msts[1<<MN],memo[1<<MN];
std::bitset<MN>vis;
std::vector<int>masks[MN];
std::vector<pii>adj[MN];
inline bool chk_bit(int mask,int i){
    return mask&(1<<i);
}
inline int prims(int mask){
    int res=0;
    vis.reset();
    memset(dist,0x3f,sizeof dist);
    dist[31-__builtin_clz(mask)]=0;
    for(int i=1,cur;i<sz;++i){
        cur=-1;
        for(int j=0;j<N;++j)
            if(chk_bit(mask,j)&&!vis[j]&&(!~cur||dist[j]<dist[cur]))
                cur=j;
        if(!~cur) break;
        vis[cur]=1;
        for(pii p:adj[cur])
            if(chk_bit(mask,p.first)&&!vis[p.first])
                dist[p.first]=std::min(dist[p.first],p.second);
    }
    for(int i=0;i<N;++i)
        if(chk_bit(mask,i)){
            res+=dist[i];
            res=std::min(res,INF);
        }
    return res;
}
int dp(int mask){
    if(~memo[mask]) return memo[mask];
    int cnt=__builtin_popcount(mask);
    if(cnt<sz) return INF;
    if(cnt==sz) return msts[mask];
    int top=31-__builtin_clz(mask);
    memo[mask]=INF;
    for(int i:masks[top])
        if((i&mask)==i)
            memo[mask]=std::min(memo[mask],msts[i]+dp(mask^i));
    return memo[mask];
}
int main(){
    scanf("%d%d%d",&N,&M,&K);
    if(N%K) return puts("-1")&&0;
    sz=N/K;
    for(int i=0,a,b,c;i<M;++i){
        scanf("%d%d%d",&a,&b,&c);
        adj[--a].emplace_back(--b,c);
        adj[b].emplace_back(a,c);
    }
    for(int i=(1<<sz)-1;i<(1<<N);++i){
        if(__builtin_popcount(i)!=sz) continue;
        msts[i]=prims(i);
        if(msts[i]<INF)
            masks[31-__builtin_clz(i)].emplace_back(i);
    }
    memset(memo,-1,sizeof memo);
    printf("%d",dp((1<<N)-1)==INF?-1:dp((1<<N)-1));
}
