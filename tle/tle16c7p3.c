#include <stdio.h>

#define MAXN 1000004

int N, Q, dp[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &N);
    for(int i=1, a;i<=N;i++) {
        scanf("%d", &a);
        if(a)
            dp[i] = i;
        else
            dp[i] = dp[i - 1];
    }
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;i++) {
        scanf("%d%d", &a, &b);
        if(dp[b] ^ a)
            printf("%d\n", (b - max(a, dp[b])) & 1);
        else
            printf("%d\n", !((b - a) & 1));
    }
}
