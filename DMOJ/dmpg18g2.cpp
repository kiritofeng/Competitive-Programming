#define OPTIMIZE 0
#if OPTIMIZE
    #pragma GCC optimize "Ofast"
    #pragma GCC optimize "unroll-loops"
    #pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#endif
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
    #define DEBUG 1
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
const int MN=2e5+4,MV=104;
const ll LINF=0x3f3f3f3f3f3f3f3f;
int N,A,B,C,V[MN];
ll dp[2][MV],mn[2][MV];
inline ll S(int i){
    return 1LL*i*i;
}
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    scanf("%d%d%d%d",&N,&A,&B,&C);
    for(int i=1;i<=N;++i) scanf("%d",V+i);
    memset(dp,0x3f,sizeof dp);
    dp[0][0]=0;
    for(int i=1,b=1;i<=N;++i,b^=1){
        memset(mn,0x3f,sizeof mn);
        mn[0][0]=dp[!b][0];
        for(int j=1;j<MV;++j)
            mn[0][j]=std::min(mn[0][j-1],dp[!b][j]-1LL*j*B);
        mn[1][MV-1]=dp[!b][MV-1];
        for(int j=MV-2;~j;--j)
            mn[1][j]=std::min(mn[1][j+1],dp[!b][j]);
        for(int j=0;j<MV;++j){
            dp[b][j]=std::min(dp[b][j],mn[0][j]+1LL*j*A+1LL*j*B+C*S(j-V[i]));
            dp[b][j]=std::min(dp[b][j],mn[1][j]+1LL*j*A+C*S(j-V[i]));
        }
        memset(dp[!b],0x3f,sizeof dp[!b]);
    }
    printf("%lld\n", *std::min_element(dp[N&1],dp[N&1]+MV));
    return 0;
}
