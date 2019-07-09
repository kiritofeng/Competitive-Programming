#include<bits/stdc++.h>
typedef long long ll;
const int MN=2e6+4;
int N, L, l, r, A[MN], dq[MN];
ll dp[MN], psa[MN];
inline ll sq(ll l) {
    return l*l;
}
inline __int128 f(int j, int k) {
    return dp[k] - dp[j] + __int128(psa[k] - psa[j]) * (psa[k] + psa[j] + 2 * L + 2);
}
int main() {
    scanf("%d%d",&N,&L);
    for(int i=1;i<=N;++i)
        scanf("%d",&A[i]);
    for(int i=1;i<=N;++i)
        psa[i] = psa[i-1] + A[i] + 1;
    dq[r++]=0;
    for(int i=1;i<=N;++i) {
        while(r-l > 1 and f(dq[l],dq[l+1]) < 2 * psa[i] * __int128(psa[dq[l+1]] - psa[dq[l]])) ++l;
        dp[i] = dp[dq[l]] + sq(psa[i] - psa[dq[l]] - L - 1);
        while(r-l > 1 and f(dq[r-2], dq[r-1]) * (psa[dq[r-1]] - psa[i]) < f(dq[r-1], i) * (psa[dq[r-2]] - psa[dq[r-1]])) --r;
        dq[r++] = i;
    }
    printf("%lld\n", dp[N]);
}
