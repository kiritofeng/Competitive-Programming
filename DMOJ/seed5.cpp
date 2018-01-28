#include<bits/stdc++.h>
const int MN=204,MM=1004,INF=0x3f3f3f3f;
int N,M,ecnt,ans,adj[MN],st[MN],lvl[MN];
struct edge{
    int des,flow,cap,nxt;
    edge():des(0),flow(0),cap(0),nxt(-1){}
    edge(int d,int f,int c,int n):des(d),flow(f),cap(c),nxt(n){}
}edges[MM+MN<<1];
inline void ins(int src,int des,int cap){
    edges[ecnt]=edge(des,0,cap,adj[src]);
    adj[src]=ecnt++;
    edges[ecnt]=edge(src,0,0,adj[des]);
    adj[des]=ecnt++;
}
inline bool bfs(int src,int snk){
    memset(lvl,-1,sizeof lvl);
    std::queue<int>q;
    q.push(src);
    lvl[src]=0;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=adj[cur];~i;i=edges[i].nxt)
            if(!~lvl[edges[i].des]&&edges[i].flow<edges[i].cap){
                lvl[edges[i].des]=lvl[cur]+1;
                q.push(edges[i].des);
            }
    }
    return ~lvl[snk];
}
int dfs(int src,int snk,int flow){
    if(src==snk) return flow;
    for(int &i=st[src];~i;i=edges[i].nxt){
        if(edges[i].flow<edges[i].cap&&lvl[edges[i].des]==lvl[src]+1)
            if(int f=dfs(edges[i].des,snk,std::min(edges[i].cap-edges[i].flow,flow))){
                edges[i].flow+=f;
                edges[i^1].flow-=f;
                return f;
            }
    }
    return 0;
}
int main(){
    scanf("%d",&N);
    memset(adj,-1,sizeof adj);
    for(int i=1,a;i<N;++i){
        scanf("%d",&a);
        ins(i,i+N,a);
    }
    scanf("%d",&M);
    for(int i=0,a,b;i<M;++i){
        scanf("%d%d",&a,&b);
        ins(a+N,b,INF);
    }
    while(bfs(1,N)){
        memcpy(st,adj,sizeof adj);
        while(int f=dfs(1,N,INF))
            ans+=f;
    }
    printf("%d",ans);
}
