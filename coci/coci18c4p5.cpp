#include<bits/stdc++.h>
const int MN = 1e5+4, BS_ITS = 100;
int N, K;
long double lo,hi,dp[MN];
int l,r,dq[MN],cnt[MN];
inline bool solve(long double lambda) {
    dp[0] = 0;
    l = r = 0;
    cnt[0] = dq[r++] = 0;
    for(int j=1; j<=N; ++j) {
        while(r - l > 1 && j * (dp[dq[l + 1]] - dp[dq[l]]) >= dq[l + 1] - dq[l]) ++l;
        dp[j] = dp[dq[l]] + 1.0 * (j - dq[l]) / j + lambda;
        cnt[j] = cnt[dq[l]] + 1;
        while(r - l > 1 && (dq[r - 1] - dq[r - 2]) * (dp[j] - dp[dq[r - 1]]) >= (j - dq[r - 1]) * (dp[dq[r - 1]] - dp[dq[r - 2]])) --r;
        dq[r++] = j;
    }
    return cnt[N] <= K;
}
int main() {
    scanf("%d%d",&N, &K);
    lo = -1, hi = 0;
    for(int i=0; i < BS_ITS; ++i) {
        long double mi = (lo + hi) / 2;
        if(solve(mi)) lo = mi;
        else hi = mi;
    }
    solve(lo);
    printf("%.8Lf\n", dp[N] - hi * K);
}
