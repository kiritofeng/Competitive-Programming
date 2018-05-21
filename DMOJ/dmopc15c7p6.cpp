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
    template<typename T>
    inline void line(T t){}
    template<typename T,typename... A>
    inline void line(T t,A... a){}
    template<typename T>
    inline void array(T* first,T* last){}
    #if DEBUG
        template<typename T>
        inline void line(T t){
            std::cerr << t << std::endl;
        }
        template<typename T,typename... A>
        inline void line(T t,A... a){
            std::cerr << t << "\t";
            line(a...);
        }
        template<typename T>
        inline void array(T* first,T* last){
            for(;first!=last;++first){
                std::cerr << *first << std::endl;
            }
        }
    #endif
};
const int ML=1e5+4,MA=26;
int L,p,sz,lst,num[ML],to[ML][MA],s[ML],suf[ML],len[ML];
ll ans,cnt[ML];
char S[ML];
inline void init(){
    memset(s,0,sizeof s);
    memset(to,0,sizeof to);
    memset(suf,0,sizeof suf);
    memset(num,0,sizeof num);
    memset(len,0,sizeof len);
    p=0;
    s[p++]=-1;
    suf[0]=1;
    len[1]=-1;
    sz=2;
    lst=0;
}
inline int lnk(int v){
    while(s[p-len[v]-2]!=s[p-1]) v=suf[v];
    return v;
}
inline int ins(int i){
    s[p++]=i;
    lst=lnk(lst);
    if(!to[lst][i]){
        len[sz]=len[lst]+2;
        suf[sz]=to[lnk(suf[lst])][i];
        to[lst][i]=sz++;
    }
    lst=to[lst][i];
    debug::line("suf[lst]:", suf[lst]);
    debug::line("num[suff[lst]]:",num[suf[lst]]);
    return num[lst]=num[suf[lst]]+1;
}
int main(){
    scanf("%s",S);
    L=strlen(S);
    init();
    for(int i=0;i<L;++i)
        cnt[i]=ins(S[i]-'a');
    debug::array(cnt,cnt+L);
    for(int i=1;i<L;++i)
        cnt[i]+=cnt[i-1];
    init();
    for(int i=L-1;i;--i)
        ans+=cnt[i-1]*ins(S[i]-'a');
    printf("%lld\n",ans);
}
