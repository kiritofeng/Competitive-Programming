#include<bits/stdc++.h>
#include<bits/extc++.h>
typedef std::pair<int,int>pii;
const int MAXN=1004;
int N,R,cnt,leaves,dfn[MAXN],low[MAXN],bcc[MAXN];
std::bitset<MAXN>B,vis;
std::vector<pii>adj[MAXN];
std::unordered_set<int>t[MAXN];
void tarjan(int src,int par) {
    dfn[src]=low[src]=++cnt;
    for(pii p:adj[src]) {
        if(p.first==par) continue;
        if(!dfn[p.first]) {
            tarjan(p.first,src);
            low[src]=std::min(low[src],low[p.first]);
            if(low[p.first]>dfn[src])
                B[p.second]=1;
        } else low[src]=std::min(low[src],dfn[p.first]);
    }
}
void dfs1(int src,int cc) {
    bcc[src]=cc;
    for(pii p:adj[src]) {
        if(bcc[p.first]||B[p.second]) continue;
        dfs1(p.first,cc);
    }
}
void dfs2(int src) {
    vis[src]=1;
    for(pii p:adj[src]) {
        if(vis[p.first]) continue;
        if(bcc[p.first]^bcc[src]) {
            t[bcc[src]].insert(bcc[p.first]);
            t[bcc[p.first]].insert(bcc[src]);
        }
        dfs2(p.first);
    }
}
int main() {
    scanf("%d%d",&N,&R);
    for(int i=0,a,b;i<R;++i) {
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b,i);
        adj[b].emplace_back(a,i);
    }
    for(int i=1;i<=N;++i)
        if(!dfn[i])
            tarjan(i,i);
    cnt=0;
    for(int i=1;i<=N;++i)
        if(!bcc[i])
            dfs1(i,++cnt);
    for(int i=1;i<=N;++i)
        if(!vis[i])
            dfs2(i);
    for(int i=1;i<=N;++i)
        if(t[i].size()==1)
            ++leaves;
    printf("%d\n",leaves+1>>1);
}
