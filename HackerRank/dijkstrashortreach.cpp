#include<bits/stdc++.h>
#include<bits/extc++.h>
// typedefs
typedef long long ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;
// debugging functions
namespace debug{
    #define DEBUG 0
    template<typename T>inline void line(T t){}
    template<typename T,typename... A>inline void line(T t,A... a){}
    template<typename T>inline void array(T* first,T* last){}
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
            for(;first!=last;++first){
                std::cerr<<*first<<std::endl;
            }
        }
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
const int MN=3004;
const ll INF=0x3f3f3f3f3f3f3f3f;
int T,N,M,S;
ll dist[MN];
vii adj[MN];
std::bitset<MN>vis;
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cerr.tie(0);
    for(scanf("%d",&T);T--;){
        scanf("%d%d",&N,&M);
        for(int i=1;i<=N;++i) adj[i].clear();
        for(int i=0,a,b,c;i<M;++i){
            scanf("%d%d%d",&a,&b,&c);
            adj[a].emplace_back(b,c);
            adj[b].emplace_back(a,c);
        }
        scanf("%d",&S);
        memset(dist,0x3f,sizeof dist);
        dist[S]=0;
        vis.reset();
        for(int i=1,st;i<=N;++i){
            st=-1;
            for(int j=1;j<=N;++j){
                if(vis[j]) continue;
                if(!~st||dist[st]>dist[j]) st=j;
            }
            if(!~st) break;
            vis[st]=1;
            for(pii p:adj[st]){
                if(vis[p.first]) continue;
                if(dist[p.first]>dist[st]+p.second)
                    dist[p.first]=dist[st]+p.second;
            }
        }
        for(int i=1;i<=N;++i)
            if(i!=S) printf("%lld ",dist[i]==INF?-1:dist[i]);
        printf("\n");
    }
    return 0;
}
