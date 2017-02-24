#include <stdio.h>
#include <string.h>

int N, t[104][104], m[104][104];

#define max(a, b) (a > b ? a : b)

int dfs(int x, int y) {
    if(m[x][y] ^ -1) return m[x][y];
    if(x < N) return m[x][y] = max(dfs(x + 1, y), dfs(x + 1, y + 1)) + t[x][y];
    return 0;

}

int main() {
    scanf("%d", &N);
    for(int i=0;i<N;i++)
        for(int j=0;j<=i;j++)
            scanf("%d", &t[i][j]);
    memset(m, -1, sizeof m);
    printf("%d", dfs(0, 0));
    return 0;
}
