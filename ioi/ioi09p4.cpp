#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
int N, M, A[54][54], psa[54][54], memo[54][54][54][54];

int dp(int X1, int Y1, int X2, int Y2) {
    if(X1 == X2 && Y1 == Y2) return memo[X1][Y1][X2][Y2] = 0;
    if(~memo[X1][Y1][X2][Y2]) return memo[X1][Y1][X2][Y2];
    memo[X1][Y1][X2][Y2] = psa[Y2][X2] - psa[Y2][X1-1] - psa[Y1-1][X2] + psa[Y1-1][X1-1];
    int tmp = INF;
    for(int i=X1+1;i<=X2;++i)
        tmp = min(tmp, dp(X1, Y1, i-1, Y2) + dp(i, Y1, X2, Y2));
    for(int i=Y1+1;i<=Y2;++i)
        tmp = min(tmp, dp(X1, Y1, X2, i-1) + dp(X1, i, X2, Y2));
    return memo[X1][Y1][X2][Y2] += tmp;
}

int main() {
    scanf("%d%d", &N, &M);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            scanf("%d", &A[i][j]);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=M;++j)
            psa[i][j] = A[i][j] + psa[i][j-1] + psa[i-1][j] - psa[i-1][j-1];
    memset(memo, -1, sizeof memo);
    printf("%d", dp(1, 1, M, N));
}
