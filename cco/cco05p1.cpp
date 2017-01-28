#include <bits/stdc++.h>

using namespace std;

//Does brute force pass?

int N, M, i, j, k, grid[104][104];
bitset<104>vis[104];

inline bool valid(int x, int y) {
    return !vis[y][x] && (grid[y][x] == i || grid[y][x] == j || grid[y][x] == k);
}

void dfs(int x, int y) {
    vis[y][x] = 1;
    if(x && valid(x - 1, y)) dfs(x - 1, y);
    if(y && valid(x, y-1)) dfs(x, y - 1);
    if((x + 1 < N) && valid(x + 1, y)) dfs(x + 1, y);
    if((y + 1 < M) && valid(x, y + 1)) dfs(x, y + 1);
}

int main() {
    scanf("%d%d", &N, &M);
    for(i=0;i<M;i++)
        for(j=0;j<N;j++) {
            scanf("%d", &grid[i][j]);
        }
    for(i=0;i<10;i++)
        for(j=i;j<10;j++)
            for(k=j;k<10;k++)
                for(int l=0;l<N;l++)
                    if(!vis[0][l]) {
                        for(int m=0;m<M;m++) vis[m].reset();
                        if(valid(l, 0)) dfs(l, 0);
                        if(vis[M-1].count()) {
                            return printf("%d %d %d", i, j, k) & 0;
                        }
                    }
    printf("-1 -1 -1");
}
