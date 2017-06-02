#include <bits/stdc++.h>

using namespace std;

int W, H, N, M, G[252][252];
vector<int>F;
int main() {
    scanf("%d %d %d", &W, &H, &N);
    for(int i=1;i<=H;i++) {
        for(int j=1;j<=W;j++) {
            scanf("%d", &G[j][i]);
        }
    }
    for(int i=1;i<=W;i++) {
        for(int j=1;j<=H;j++) {
            G[i][j]+=G[i-1][j]+G[i][j-1]-G[i-1][j-1];
        }
    }
    for(int i=0;i<=W;i++) {
        for(int j=0;j<=H;j++) {
            for(int k=1;k<=W;k++) {
                int a=min(i+k, W), b = min(j+N/k, H);
                M=max(M, G[a][b]-G[a][j]-G[i][b]+G[i][j]);
                if(DEBUG) printf("%d %d %d %d %d\n", i+1, j+1, a, b, G[a][b]-G[a][j]-G[i][b]+G[i][j]);
            }
        }
    }
    printf("%d", M);
}
