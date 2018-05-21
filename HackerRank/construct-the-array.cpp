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
const int MN=1e5+4,MOD=1e9+7;
int N,K,X;
ll dp[MN][2];
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    std::cerr.tie(0);
    scanf("%d%d%d",&N,&K,&X);
    dp[N][X!=1]=1;
    for(int i=N-1;i;--i){
        dp[i][0]=dp[i+1][1];
        dp[i][1]=((K-1)*dp[i+1][0]+(K-2)*dp[i+1][1])%MOD;
    }
    printf("%lld\n",dp[1][0]);
    return 0;
}
