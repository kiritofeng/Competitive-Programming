#include<bits/stdc++.h>
const int MN = 1e6+4,MM=22,MOD=1e9+7;
int N,M,ans,pw[MN],dp[1<<MM];
int main() {
    scanf("%d%d",&N, &M);
    pw[0] = 1;
    for(int i=1;i<=N;++i)
        pw[i] = (2 * pw[i-1]) % MOD;
    for(int i=0,msk,k;i<N;++i) {
        msk = 0;
        scanf("%d",&k);
        for(int j=0,a;j<k;++j) {
            scanf("%d",&a);
            msk |= 1<<a;
        }
        dp[msk] += 1;
    }
    for(int i=1;i<=M;++i)
        for(int j=0;j<(1<<M+1);++j)
            if(j & (1<<i)) dp[j] += dp[j^(1<<i)];
    for(int i=0;i<(1<<M+1);++i)
        if(M - __builtin_popcount(i) & 1)
            ans = (ans - pw[dp[i]] + MOD) % MOD;
        else
            ans = (ans + pw[dp[i]]) % MOD;
    printf("%d\n", ans);
}
