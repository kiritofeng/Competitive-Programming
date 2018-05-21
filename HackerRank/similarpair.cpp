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
const int MN=1e5+4;
int N,K,indeg[MN];
vi adj[MN];
ll ans,bit[MN];
inline void upd(int p,int i){
    for(;p<MN;p+=p&-p)
        bit[p]+=i;
}
inline ll qry(int p){
    ll res=0;
    for(;p;p-=p&-p)
        res+=bit[p];
    return res;
}
void dfs(int src){
    ans+=qry(std::min(src+K,N))-qry(std::max(src-K,1)-1);
    upd(src,1);
    for(int i:adj[src])
        dfs(i);
    upd(src,-1);
}
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cerr.tie(0);
    scanf("%d%d",&N,&K);
    for(int i=1,a,b;i<N;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        ++indeg[b];
    }
    for(int i=1;i<=N;++i)
        if(!indeg[i]) dfs(i);
    printf("%lld\n",ans);
    return 0;
}
