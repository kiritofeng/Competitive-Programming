#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,avx,abm,mmx,popcnt,tune=native"
#include<bits/stdc++.h>
typedef long long ll;
const int MN=3004;
int N,M;
std::bitset<MN> in[MN],out[MN];
ll ans;
int main(){
    scanf("%d%d",&N,&M);
    for(int i=0,a,b;i<M;++i){
        scanf("%d%d",&a,&b);
        out[a][b]=1;
        in[b][a]=1;
    }
    for(int i=1;i<=N;++i)
        for(int j=1;j<i;++j){
            std::bitset<MN> tmp1=in[i]&in[j],tmp2=out[i]&out[j],tmp3=tmp1&tmp2;
            ans+=1LL*tmp1.count()*tmp2.count()-tmp3.count();
        }
    printf("%lld\n",ans);
}
