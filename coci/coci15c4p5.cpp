#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e5+4;
int N, val[MN], dsu[MN], A[MN];
int acnt, adj[MN], des[MN*2], wei[MN], nxt[MN*2];
ll ans[MN];
std::unordered_map<int,int>paths[MN];
inline void add_edge(int u, int v, int w) {
    wei[acnt/2] = w;
    des[acnt] = v;
    nxt[acnt] = adj[u];
    adj[u] = acnt++;
    des[acnt] = u;
    nxt[acnt] = adj[v];
    adj[v] = acnt++;
}
void dfs(int u, int p, int v=0) {
    val[u] = v;
    for(int i=adj[u]; ~i; i=nxt[i]) {
        if(des[i] == p) continue;
        dfs(des[i], u, v^wei[i/2]);
    }
}
int root(int u) {
    return dsu[u] < 0 ? u : dsu[u] = root(dsu[u]);
}
inline ll mrg(int u, int v) {
    u = root(u), v = root(v);
    assert(u != v);
    ll ret = 0;
    if(dsu[u] > dsu[v]) std::swap(u, v);
    dsu[u] += dsu[v];
    dsu[v] = u;
    for(const auto &p : paths[v]) {
        ret += 1LL * p.second * paths[u][p.first];
        paths[u][p.first] += p.second;
    }
    return ret;
}
int main() {
    memset(adj, -1, sizeof adj);
    memset(dsu, -1, sizeof dsu);
    scanf("%d", &N);
    for(int i=1,a,b,c; i<N; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        add_edge(a,b,c);
    }
    dfs(1, 0);
    for(int i=1; i<=N; ++i)
        paths[i][val[i]] = 1;
    for(int i=1; i<N; ++i)
        scanf("%d", &A[i]);
    for(int i=1; i<N; ++i) {
        ans[i] = mrg(des[2*(A[N-i]-1)], des[2*(A[N-i]-1)+1]);
        ans[i] += ans[i - 1];
    }
    for(int i=N-1; i>=0; --i) {
        printf("%lld\n", ans[i]);
    }
}
