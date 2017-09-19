#include<bits/stdc++.h>
using namespace std;
const int MAXN=504,MAXT=1e9+4;
typedef tuple<int,int,int> ti3;
int N,M,K,Q,lo=0,hi=MAXT,mid,psa[MAXN][MAXN];
ti3 broken[MAXN*MAXN];
int main() {
    scanf("%d%d%d%d",&N,&M,&K,&Q);
    for(int i=0,a,b,c;i<Q;++i) {
        scanf("%d%d%d",&a,&b,&c);
        broken[i]=make_tuple(c,a,b);
    }
    sort(broken,broken+Q);
    while(lo<=hi) {
        mid=lo+hi>>1;
        memset(psa,0,sizeof psa);
        for(int i=0;i<Q&&get<0>(broken[i])<=mid;++i)
            psa[get<1>(broken[i])][get<2>(broken[i])]=1;
        bool good=0;
        for(int i=1;i<=N;++i)
            for(int j=1;j<=M;++j) {
                psa[i][j]+=psa[i][j-1]+psa[i-1][j]-psa[i-1][j-1];
                good |= psa[i][j]-psa[i][j-K]-psa[i-K][j]+psa[i-K][j-K]==K*K;
            }
        if(good) hi=mid-1;
        else lo=mid+1;
    }
    printf("%d",lo>MAXT?-1:lo);
}
