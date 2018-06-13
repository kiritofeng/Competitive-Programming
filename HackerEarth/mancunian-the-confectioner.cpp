#include<bits/stdc++.h>
#include<bits/extc++.h>
// useful macros
#define gets(x) fgets(x,sizeof(x),stdin)
#define all(x) x.begin(),x.end()
// typedefs
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;
// input and output overrides
template<typename T1,typename T2>
std::istream &operator >>(std::istream &in,std::pair<T1,T2> &p){
    in>>p.first>>p.second;
    return in;
}
template<typename T1,typename T2>
std::ostream &operator <<(std::ostream &out,std::pair<T1,T2> p){
    out<<"("<<p.first<<","<<p.second<<")";
    return out;
}
// debugging functions
namespace debug{
    #define DEBUG 0
    #if DEBUG
        template<typename T>
        inline void line(T t){
            std::cerr<<t<<std::endl;
        }
        template<typename T,typename... A>
        inline void line(T t,A... a){
            std::cerr<<t<<"\t";
            line(a...);
        }
        template<typename T>
        inline void array(T* first,T* last){
            for(;first!=last;++first)
                std::cerr<<*first<<std::endl;
        }
        template<class InputIt>
        inline void iterator(InputIt first,InputIt last){
            for(;first!=last;++first)
                std::cerr<<*first<<std::endl;
        }
        template<typename... A>
        inline void printf(const char *S,A... a){
            fprintf(stderr,S,a...);
        }
    #else
        template<typename T>inline void line(T t){}
        template<typename T,typename... A>inline void line(T t,A... a){}
        template<typename T>inline void array(T* first,T* last){}
        template<class InputIt>inline void iterator(InputIt first,InputIt last){}
        template<typename... A>inline void printf(const char *S,A... a){}
    #endif
};
// bitmask manipulations
inline bool cb(int msk,int i){
    return msk&(1<<i);
}
inline int sb(int msk,int i){
    return msk|(1<<i);
}
inline int ub(int msk,int i){
    return msk&~(1<<i);
}
inline int tb(int msk,int i){
    return msk^(1<<i);
}
const int INF=0x3f3f3f3f,MN=204,MM=204;
struct edge{
    int v,f,c,n;
}edges[2*MN*MN];
int N,M,ecnt,A[MN],B[MM],adj[MN+MM],lvl[MN+MM],st[MN+MM];
std::queue<int>q;
ll sum;
inline void add_edge(int u,int v,int c){
    edges[ecnt]={v,0,c,adj[u]};
    adj[u]=ecnt++;
    edges[ecnt]={u,0,0,adj[v]};
    adj[v]=ecnt++;
}
inline bool bfs(int src,int snk){
    memset(lvl,-1,sizeof lvl);
    lvl[src]=0;
    q.push(src);
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int e=adj[cur];~e;e=edges[e].n)
            if(!~lvl[edges[e].v]&&edges[e].f<edges[e].c){
                lvl[edges[e].v]=lvl[cur]+1;
                q.push(edges[e].v);
            }
    }
    return ~lvl[snk];
}
ll dfs(int src,int snk,int flow){
    if(src==snk) return flow;
    for(int &e=st[src];~e;e=edges[e].n){
        if(edges[e].f<edges[e].c&&lvl[edges[e].v]==lvl[src]+1)
            if(ll f=dfs(edges[e].v,snk,std::min(flow,edges[e].c-edges[e].f))){
                edges[e].f+=f;
                edges[e^1].f-=f;
                return f;
            }
    }
    return 0;
}
inline ll dinic(int src,int snk){
    ll ret=0;
    while(bfs(src,snk)){
        memcpy(st,adj,sizeof adj);
        while(ll tmp=dfs(src,snk,INF)) ret+=tmp;
    }
    return ret;
}
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cerr.tie(0);
    memset(adj,-1,sizeof adj);
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i){
        scanf("%d",A+i);
        add_edge(0,i,A[i]);
        sum+=A[i];
    }
    for(int i=1;i<=M;++i){
        scanf("%d",B+i);
        add_edge(N+i,N+M+1,B[i]);
    }
    for(int i=1,a;i<=N;++i){
        for(int j=1;j<=M;++j){
            scanf("%d",&a);
            if(a) add_edge(i,N+j,INF);
        }
    }
    printf("%lld\n",sum-dinic(0,N+M+1));
    return 0;
}
