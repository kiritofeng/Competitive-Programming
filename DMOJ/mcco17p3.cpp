#include<bits/stdc++.h>
const int MN = 15e4+4, MD = 15e4+4, MQ = 15e4+4;
int N, D, Q;
int dsu1[MN], dsu2[MN];
int top[MN];
int par[MN], depth[MN];
int edges[MD][3];
int acnt, adj[MN], nxt[MN*2];
int ans[MQ];
std::unordered_set<int>qrys[MN];

inline void add_edge(int u, int v, int i) {
    nxt[i*2] = adj[v];
    adj[v] = i*2;
    nxt[i*2+1] = adj[u];
    adj[u] = i*2+1;
}

void dfs1(int u=0, int p=-1, int d=1) {
    par[u] = p;
    depth[u] = d;
    for(int i = adj[u]; ~i; i = nxt[i]) {
        if(edges[i/2][i&1] == p) continue;
        dfs1(edges[i/2][i&1], u, d + 1);
    }
}

int root(int *dsu, int u) {
    return dsu[u] < 0 ? u : dsu[u] = root(dsu, dsu[u]);
}

inline bool merge1(int u, int v) {
    u = root(dsu1, u), v = root(dsu1, v);
    if(u == v) return 0;
    if(dsu1[u] < dsu1[v]) std::swap(u, v);
    dsu1[v] += dsu1[u];
    dsu1[u] = v;
    return 1;
}

inline int merge2(int u, int v, int t) {
    u = root(dsu2, u), v = root(dsu2, v);
    assert(u != v);
    if(qrys[u].size() < qrys[v].size()) std::swap(u, v);
    for(int i : qrys[v]) {
        auto it = qrys[u].find(i);
        if(it != qrys[u].end()) {
            ans[i] = t;
            qrys[u].erase(it);
        } else qrys[u].insert(i);
        qrys[v].clear();
    }
    if(depth[top[u]] > depth[top[v]]) top[u] = top[v];
    dsu2[v] = u;
    return top[u];
}

int main() {
    scanf("%d%d%d", &N, &D, &Q);
    memset(dsu1, -1, sizeof dsu1);
    memset(adj, -1, sizeof adj);
    for(int i = 0; i < D; ++i) {
        scanf("%d%d", &edges[i][0], &edges[i][1]);
        if(merge1(edges[i][0], edges[i][1])) {
            add_edge(edges[i][0], edges[i][1], i);
            edges[i][2] = 1;
        }
    }
    for(int i = 0; i <= N; ++i)
        if(!depth[i]) dfs1(i);
    memset(dsu2, -1, sizeof dsu2);
    memset(ans, -1, sizeof ans);
    for(int i = 0, a, b; i < Q; ++i) {
        scanf("%d%d", &a, &b);
        if(a == b) // stupid
            ans[i] = 0;
        else {
            qrys[a].insert(i);
            qrys[b].insert(i);
        }
    }
    for(int i = 0; i <= N; ++i)
        top[i] = i;
    for(int i = 0; i < D; ++i) {
        if(!edges[i][2]) {
            int u = top[root(dsu2, edges[i][0])], v = top[root(dsu2, edges[i][1])];
            while(u != v) {
                if(depth[u] < depth[v]) std::swap(u, v);
                u = merge2(u, par[u], i);
                v = top[root(dsu2, v)];
            }
        }
    }
    for(int i = 0; i < Q; ++i)
        printf("%d\n", ans[i]);
}
