// gotta go fast
#define OPTIMIZE 0
#if OPTIMIZE
    #pragma GCC optimize "Ofast"
    #pragma GCC optimize "unroll-loops"
    #pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#endif
// standard headers
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
const int MN=400;
const double eps=1e-5;
int N,cnt;
struct titan{
    int x,y1,y2;
}T[MN];
std::pair<double,double>ans;
inline bool lt(double d1,double d2){
    // this is stupid
    if(fabs(d1-d2)<eps) return 1;
    return d1<d2;
}
inline bool collide(titan t,double y){
    return lt(t.y1,y)&&lt(y,t.y2);
}
inline void test(int x1,int y1,int x2,int y2){
    int c=0;
    double m=1.0*(y2-y1)/(x2-x1);
    double a=y1-m*x1;
    double b=m*100+a;
    if(a<0||b<0) return;
    for(int i=1;i<=N;++i){
        double tmp=m*T[i].x+a;
        if(collide(T[i],tmp)) c++;
    }
    if(c>cnt){
        cnt=c;
        ans={a,b};
    }else if(c==cnt){
        ans=std::min(ans,{a,b});
    }
}
int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    scanf("%d",&N);
    for(int i=1;i<=N;++i) scanf("%d%d%d",&T[i].x,&T[i].y1,&T[i].y2);
    for(int i=0;i<=N;++i){
        for(int j=i+1;j<=N;++j){
            if(T[i].x==T[j].x) continue;
            test(T[i].x,T[i].y1,T[j].x,T[j].y1);
            test(T[i].x,T[i].y1,T[j].x,T[j].y2);
            test(T[i].x,T[i].y2,T[j].x,T[j].y1);
            test(T[i].x,T[i].y2,T[j].x,T[j].y2);
        }
    }
    printf("%d\n%.4lf\n%.4lf\n",cnt,ans.first,ans.second);
    return 0;
}
