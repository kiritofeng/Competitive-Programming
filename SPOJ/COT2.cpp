// because I *really* don't trust any constant factors
#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,popcnt,avx,mmx,abm,tune=native"
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define all(x) x.begin(),x.end()
const int MN=4e4+4,MM=1e5+4,MLOG=16,RT=200;
int N,M,tcnt,res,ans[MM],W[MN],cnt[MN],ein[MN],eout[MN],tour[MN<<1],depth[MN],st[MN][MLOG];
std::vector<int>V,adj[MN];
std::bitset<MN>vis;
struct qry{
    int l,r,lca,i;
    bool operator <(const qry &q) const{
        return l/RT<q.l/RT||(l/RT==q.l/RT&&r<q.r);
    }
}qrys[MM];
void dfs(int src,int p,int d=1){
    depth[src]=d;
    st[src][0]=p;
    tour[ein[src]=++tcnt]=src;
    for(int i:adj[src]){
        if(i==p) continue;
        dfs(i,src,d+1);
    }
    tour[eout[src]=++tcnt]=src;
}
inline void build(){
    for(int j=1;j<MLOG;++j)
        for(int i=1;i<=N;++i)
            if(~st[i][j-1])
                st[i][j]=st[st[i][j-1]][j-1];
            else
                st[i][j]=-1;
}
inline int lca(int u,int v){
    if(depth[u]<depth[v]) std::swap(u,v);
    for(int i=MLOG-1;i>=0;--i)
        if(~st[u][i]&&depth[st[u][i]]>=depth[v])
            u=st[u][i];
    if(u==v) return u;
    for(int i=MLOG-1;i>=0;--i)
        if(st[u][i]!=st[v][i])
            u=st[u][i],v=st[v][i];
    return st[u][0];
    
}
inline void chk(int t){
    if(vis[t]&&!--cnt[W[t]]) --res;
    else if(!vis[t]&&!cnt[W[t]]++) ++res;
    vis.flip(t);
}
int main(){
    // do you mind telling us in the problem statement
    // that there is more than one test case per input
    while(~scanf("%d%d",&N,&M)){
        V.clear();
        for(int i=1;i<=N;++i){
            scanf("%d",W+i);
            V.emplace_back(W[i]);
        }
        std::sort(all(V));
        V.erase(std::unique(all(V)),V.end());
        for(int i=1;i<=N;++i)
            W[i]=std::lower_bound(all(V),W[i])-V.begin();
        for(int i=1;i<=N;++i)
            adj[i].clear();
        for(int i=1,a,b;i<N;++i){
            scanf("%d%d",&a,&b);
            adj[a].emplace_back(b);
            adj[b].emplace_back(a);
        }
        dfs(1,-1);
        build();
        for(int i=0,a,b,l;i<M;++i){
            scanf("%d%d",&a,&b);
            l=lca(a,b);
            if(ein[b]<ein[a]) std::swap(a,b);
            if(a==l||b==l) qrys[i]={ein[a],ein[b],-1,i};
            else qrys[i]={eout[a],ein[b],l,i};
        }
        std::sort(qrys,qrys+M);
        vis.reset();
        memset(cnt,0,sizeof cnt);
        res=0;
        chk(tour[1]);
        for(int i=0,l=1,r=1;i<M;++i){
            while(r<qrys[i].r) chk(tour[++r]);
            while(l>qrys[i].l) chk(tour[--l]);
            while(r>qrys[i].r) chk(tour[r--]);   
            while(l<qrys[i].l) chk(tour[l++]);
            if(~qrys[i].lca) chk(qrys[i].lca);
            ans[qrys[i].i]=res;
            if(~qrys[i].lca) chk(qrys[i].lca);
        }
        for(int i=0;i<M;printf("%d\n",ans[i++]));
    }
}
