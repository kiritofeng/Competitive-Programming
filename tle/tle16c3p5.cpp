#include <bits/stdc++.h>

using namespace std;

int R, C, M, u, v, sq[352];
stack<int>sz;
bool g[352][352][352];

void dfs(int x, int y, int lvl=1) {
    if(g[lvl][x][y]) {
        g[lvl][x][y] = 0;
        dfs(x - 1, y - 1, lvl + 1);
        dfs(x - 1, y, lvl + 1);
        dfs(x, y - 1, lvl + 1);
        dfs(x, y, lvl + 1);
        if(!--sq[lvl])
            while(sz.top() >= lvl) sz.pop();
    }
}

int main() {
    scanf("%d%d%d", &R, &C, &M);
    sz.push(0);
    for(int i=0;i<min(R, C);) {
        for(int j=1;j<=R - i;j++) {
            for(int k=1;k<=C - i;k++) {
                g[i + 1][j][k] = 1;
                sq[i + 1]++;
            }
        }
        sz.push(++i);
    }
    for(int i=0;i<M;i++) {
        scanf("%d%d", &u, &v);
        dfs(u, v);
        printf("%d\n", sz.top());
    }
    return 0;
}
