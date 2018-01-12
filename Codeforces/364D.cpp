#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,avx,abm,mmx,popcnt,tune=native"
#define rand32() ((rand()&0xffff)<<15|(rand()&0xffff))
#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e6+4,MIT=10+(rand()&3);
int N,fcnt,cnt[MN];
ll ans=1,A[MN],G[MN];
ll gcd(ll a,ll b){
    while(a&&b) a>b?a%=b:b%=a;
    return a|b;
}
int main(){
    srand(time(0));
    scanf("%d",&N);
    for(int i=0;i<N;scanf("%lld",A+i++));
    for(int i=0,ind;i<MIT;++i){
        ind=rand32()%N;
        fcnt=0;
        for(int j=0;j<N;++j)
            G[j]=gcd(A[j],A[ind]);
        std::sort(G,G+N);
        cnt[0]=0;
        for(int j=0,k=0;j<N;++j)
            if(G[k]==G[j])
                ++cnt[fcnt];
            else{
                G[++k]=G[j];
                cnt[++fcnt]=1;
            }
        for(int j=0,c;j<=fcnt;++j){
            c=0;
            for(int k=0;k<=fcnt;++k)
                if(!(G[k]%G[j]))
                    c+=cnt[k];
            if(c*2>=N) ans=std::max(ans,G[j]);
        }
    }
    printf("%lld\n",ans);
}
