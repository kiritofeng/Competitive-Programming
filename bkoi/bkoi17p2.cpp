#include<bits/stdc++.h>
#define allOf(_) (_).begin(), (_).end()
const int MN = 1e5+4;
int N, M, K, val[MN], vid[MN];
int ecnt, adj[MN], des[MN*2], nxt[MN*2], eid[MN];
int tcnt, tin[MN];
int par[MN], sz[MN], hvy[MN], top[MN], depth[MN];
std::vector<int> ans;
inline void add_edge(int u, int v) {
    des[ecnt] = v;
    nxt[ecnt] = adj[u];
    adj[u] = ecnt++;
}
void dfs1(int u=1, int p=0) {
    par[u] = p;
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    for(int i = adj[u]; ~i; i = nxt[i]) {
        if(des[i] == p) continue;
        vid[des[i]] = eid[i/2];
        dfs1(des[i], u);
        sz[u] += sz[des[i]];
        if(!hvy[u] || sz[des[i]] > sz[hvy[u]]) hvy[u] = des[i];
    }
}
void dfs2(int u=1, int t=1) {
    top[u] = t;
    tin[u] = ++tcnt;
    if(hvy[u]) dfs2(hvy[u], t);
    for(int i = adj[u]; ~i; i = nxt[i]) {
        if(des[i] == par[u] || des[i] == hvy[u]) continue;
        dfs2(des[i], des[i]);
    }
}
inline int lca(int u, int v) {
    while(top[u] != top[v]) {
        if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
        u = par[top[u]];
    }
    return depth[u] < depth[v] ? u : v;
}
void dfs3(int u=1) {
    for(int i = adj[u]; ~i; i = nxt[i]) {
        if(des[i] == par[u]) continue;
        dfs3(des[i]);
        val[u] += val[des[i]];
    }
}
int main() {
    scanf("%d%d%d", &N, &M, &K);
    memset(adj, -1, sizeof adj);
    for(int i = 1, a, b; i < N; ++i) {
        scanf("%d%d", &a, &b);
        eid[ecnt/2] = i;
        add_edge(a, b);
        add_edge(b, a);
    }
    dfs1();
    dfs2();
    for(int i = 0, a, b; i < M; ++i) {
        scanf("%d", &a);
        std::vector<int> nei;
        int all_lca = 0;
        for(int j = 0; j < a; ++j) {
            scanf("%d", &b);
            nei.push_back(b);
            val[b] += 1;
        }
        std::sort(allOf(nei), [=](const int &a, const int &b) {
                    return tin[a] < tin[b];
                });
        for(int j = 1; j < nei.size(); ++j) {
            int l = lca(nei[j-1], nei[j]);
            val[l] -= 1;
            if(!all_lca || depth[l] < depth[all_lca]) all_lca = l;
        }
        val[all_lca] -= 1;
    }
    dfs3();
    for(int i = 2; i <= N; ++i) {
        if(val[i] >= K) ans.push_back(vid[i]);
    }
    std::sort(allOf(ans));
    printf("%lu\n", ans.size());
    for(int i : ans) {
        printf("%d ", i);
    }
}
