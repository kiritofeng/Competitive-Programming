#include<bits/stdc++.h>
#include<bits/extc++.h>
typedef long long ll;
const int MAXN=5004,MAXM=30004,INF=0x3f3f3f3f;
int N,M,eCnt,lvl[MAXN],adj[MAXN],st[MAXN];
struct edge {
    int des,flow,cap,nxt;
    edge():des(0),flow(0),cap(0),nxt(-1){};
    edge(int d,int f,int c,int n):des(d),flow(f),cap(c),nxt(n){};
}E[MAXM<<1];
ll ans;
std::queue<int>q;
int dfs(int src,int sink,int flow) {
    if(src==sink) return flow;
    for(int &i=st[src],df;~i;i=E[i].nxt) {
        if(E[i].flow<E[i].cap&&lvl[E[i].des]==lvl[src]+1)
            if(df=dfs(E[i].des,sink,std::min(E[i].cap-E[i].flow,flow))) {
                E[i].flow+=df;
                E[i^1].flow-=df;
                return df;
            }
    }
    return 0;
}
bool bfs(int src,int sink) {
    memset(lvl,-1,sizeof lvl);
    lvl[src]=0;
    q.push(src);
    while(!q.empty()) {
        int cur=q.front();
        q.pop();
        for(int i=adj[cur];~i;i=E[i].nxt)
            if(!~lvl[E[i].des]&&E[i].flow<E[i].cap) {
                lvl[E[i].des]=lvl[cur]+1;
                q.push(E[i].des);
            }
    }
    return ~lvl[sink];
}
int main() {
    scanf("%d%d",&N,&M);
    memset(adj,-1,sizeof adj);
    for(int i=0,a,b,c;i<M;++i) {
        scanf("%d%d%d",&a,&b,&c);
        if(a==b) continue;
        E[eCnt]=edge(b,0,c,adj[a]);
        adj[a]=eCnt++;
        E[eCnt]=edge(a,0,c,adj[b]);
        adj[b]=eCnt++;
    }
    while(bfs(1,N)) {
        memcpy(st,adj,sizeof adj);
        while(int flow=dfs(1,N,INF))
            ans+=flow;
    }
    printf("%lld\n",ans);
}
