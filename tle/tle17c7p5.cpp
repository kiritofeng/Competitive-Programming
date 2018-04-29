#include<bits/stdc++.h>
#ifdef DEBUG
    #define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
    #define eprintf(...)
#endif
typedef std::pair<int,int>pii;
const int MN=104,INF=0x3f3f3f3f;
const double EPS=1e-6;
int N,ecnt,adj[MN*2],st[MN*2],pre[MN*2];
pii A[MN*2];
double dist[MN*2];
struct edge{
    int src,des,flow,cap,nxt;
    double cost;
    edge():src(-1),des(-1),flow(0),cap(0),cost(0),nxt(-1){}
    edge(int u,int v,int f,int cp,double cst,int n):src(u),des(v),flow(f),cap(cp),cost(cst),nxt(n){}
}edges[MN*MN*2];
inline int SQ(int i){
    return i*i;
}
inline double dst(pii p1,pii p2){
    return sqrt(SQ(p1.first-p2.first)+SQ(p1.second-p2.second));
}
inline void add_edge(int u,int v,int cap,double cost){
    edges[ecnt]=edge(u,v,0,cap,cost,adj[u]);
    adj[u]=ecnt++;
    edges[ecnt]=edge(v,u,0,0,-cost,adj[v]);
    adj[v]=ecnt++;
}
inline bool spfa(int src,int snk){
    std::deque<int>dq;
    std::bitset<MN*2>vis;
    std::fill(dist,dist+2*N+2,1e18);
    memset(pre,-1,sizeof pre);
    dist[src]=0;
    dq.push_back(src);
    vis[src]=1;
    while(!dq.empty()){
        int cur=dq.front();
        dq.pop_front();
        vis[cur]=0;
        for(int i=adj[cur];~i;i=edges[i].nxt){
            if(edges[i].flow<edges[i].cap&&dist[edges[i].des]>dist[cur]+edges[i].cost+EPS){
                pre[edges[i].des]=cur;
                dist[edges[i].des]=dist[cur]+edges[i].cost;
                if(!vis[edges[i].des]){
                    vis[edges[i].des]=1;
                    if(dq.empty()||dist[dq.front()]>dist[edges[i].des])
                        dq.push_front(edges[i].des);
                    else
                        dq.push_back(edges[i].des);
                }
            }
        }
    }
    return dist[snk]<1e18;
}
inline std::pair<int,double>dfs(int src,int snk,int flow,double cost){
    if(src==snk) return std::make_pair(flow,flow*cost);
    for(int &i=st[src];~i;i=edges[i].nxt){
        if(edges[i].flow<edges[i].cap&&pre[edges[i].des]==src){
            auto tmp=dfs(edges[i].des,snk,std::min(edges[i].cap-edges[i].flow,flow),cost+edges[i].cost);
            if(tmp.first){
                edges[i].flow+=tmp.first;
                edges[i^1].flow-=tmp.first;
                return tmp;
            }
        }
    }
    return std::make_pair(0,0.0);
}
inline std::pair<int,double> mcmf(){
    std::pair<int,double>res;
    while(spfa(0,2*N+1)){
        memcpy(st,adj,sizeof adj);
        auto f=dfs(0,2*N+1,INF,0);
        while(f.first){
            res.first+=f.first;
            res.second+=f.second;
            f=dfs(0,2*N+1,INF,0);
        }
    }
    return res;
}
int main(){
    memset(adj,-1,sizeof adj);
    scanf("%d",&N);
    for(int i=1;i<=N;++i) scanf("%d%d",&A[i].first,&A[i].second);
    for(int i=1;i<=N;++i) scanf("%d%d",&A[N+i].first,&A[N+i].second);
    for(int i=1;i<=N;++i){
        add_edge(0,i,1,0);
        for(int j=1;j<=N;++j)
            add_edge(i,N+j,1,dst(A[i],A[N+j]));
    }
    for(int i=1;i<=N;++i) add_edge(N+i,2*N+1,1,0);
    mcmf();
    for(int i=0;i<ecnt;++i){
        if(!edges[i].src||edges[i].des==2*N+1) continue;
        if(edges[i].flow!=1) continue;
        printf("%d %d\n",edges[i].src,edges[i].des-N);
    }
}
