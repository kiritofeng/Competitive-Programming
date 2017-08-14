#include <bits/stdc++.h>

using namespace std;

const int MAXN=104;
int N, ans, cnt[MAXN<<1], A[MAXN<<1], dp[MAXN<<1][MAXN<<1];
int main() {
    scanf("%d", &N);
    for(int i=1;i<=N;++i) {
        scanf("%d", &A[i]);
        A[i+N] = A[i];
    }
    for(int i=1;i<=(N<<1);++i)
        cnt[i] = cnt[i-1] + (A[i]&1);
    for(int i=1;i<=N;++i) {
        memset(dp, 0, sizeof dp);
        for(int j=0;j<N;++j)
            dp[i+j][i+j] = A[i+j]&1;
        for(int j=1;j<N;++j)
            for(int k=1;k<N-j;++k)
                dp[i+k][i+j+k] = cnt[i+j+k] - cnt[i+k-1] - min(dp[i+k][i+j+k-1], dp[i+k+1][i+j+k]);
        ans += cnt[i+N]-cnt[i] - (dp[i+1][i+N-1]<<1)>0;
    }
    printf("%d", ans);
}
