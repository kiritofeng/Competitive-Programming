#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2004;
int N, M, T, C, col[MAXN<<1];
vector< int > tour, adj[MAXN<<1], rev[MAXN<<1];
bitset< MAXN<<1 >vis;

void dfs1(int src) {
    vis[src] = 1;
    for(int i:adj[src])
        if(!vis[i])
            dfs1(i);
    tour.emplace_back(src);
}

void dfs2(int src) {
    col[src] = C;
    for(int i:rev[src])
        if(!~col[i])
            dfs2(i);
}

int main() {
    scanf("%d", &T);
    for(int i=1;i<=T;++i) {
        scanf("%d%d", &N, &M);
        for(int i=1;i<=N;++i) {
            adj[i<<1].clear();
            adj[i<<1|1].clear();
            rev[i<<1].clear();
            rev[i<<1|1].clear();
        }
        for(int i=1, a, b;i<=M;++i) {
            scanf("%d%d", &a, &b);
            adj[a<<1].emplace_back(b<<1|1);
            adj[a<<1|1].emplace_back(b<<1);
            adj[b<<1].emplace_back(a<<1|1);
            adj[b<<1|1].emplace_back(a<<1);
        }
        vis.reset();
        tour.clear();
        for(int i=1;i<=(N<<1);++i)
            if(!vis[i])
                dfs1(i);
        for(int i=1;i<=(N<<1);++i)
            for(int j:adj[i])
                rev[j].emplace_back(i);
        reverse(tour.begin(), tour.end());
        memset(col, -1, sizeof col);
        for(int i:tour)
            if(!~col[i]) {
                ++C;
                dfs2(i);
            }
        printf("Scenario #%d:\n", i);
        bool good = 1;
        for(int i=1;i<=N && good;++i)
            good &= col[i<<1]!=col[i<<1|1];
        puts(good ? "No suspicious bugs found!" : "Suspicious bugs found!");
    }
}
