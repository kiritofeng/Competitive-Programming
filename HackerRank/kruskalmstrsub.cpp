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
int N,M,dsu[MN];
ll ans;
struct edge{
    int u,v,w;
    inline bool operator < (const edge &e) const{
        return w<e.w;
    }
}E[MN*MN];
inline int find(int u){
    return dsu[u]<0?u:dsu[u]=find(dsu[u]);
}
inline bool mrg(int u,int v){
    if((u=find(u))!=(v=find(v))){
        if(dsu[u]>dsu[v]) std::swap(u,v);
        dsu[u]+=dsu[v];
        return dsu[v]=u;
    }   
    return 0;
}
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cerr.tie(0);
    scanf("%d%d",&N,&M);
    for(int i=0;i<M;++i)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
    std::sort(E,E+M);
    memset(dsu,-1,sizeof dsu);
    for(int i=0;i<M;++i){
        if(mrg(E[i].u,E[i].v)) ans+=E[i].w;
    }
    printf("%lld\n",ans);
    return 0;
}
