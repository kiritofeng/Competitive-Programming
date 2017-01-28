#include <bits/stdc++.h>

using namespace std;

int N, ans, A[404], P[404], dp[404][404];

bool solve(int l, int r) {
    if(dp[l][r] != -1) return dp[l][r];
    if(l >= r) return dp[l][r] = 1;
    for(int i=l;i<=r;i++) {
        for(int j=r;j>=i;j--) {
            if(P[i] - P[l - 1] < P[r] - P[j - 1]) break;
            if(P[i] - P[l - 1] == P[r] - P[j - 1]) {
                if(solve(l, i) && solve(i + 1, j - 1) && solve(j, r)) return dp[l][r]=1;
                break;
            }
        }
    }
    return dp[l][r]=0;
}

int main() {
    scanf("%d", &N);
    memset(dp, -1, sizeof dp);
    for(int i=1;i<=N;i++) {
        scanf("%d", &A[i]);
        P[i] = A[i] + P[i-1];
    }
    for(int i=1;i<=N;i++) {
        for(int j=i;j<=N;j++) {
            if(solve(i, j)) {
                ans = max(ans, P[j]-P[i - 1]);
            }
        }
    }
    printf("%d", ans);
}
