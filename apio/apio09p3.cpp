#include<bits/stdc++.h>
const int MN = 5e5+4, MM = 5e5+4;
int N, M, S, P, ans, ccnt, val[MN], tot[MN];
int ecnt, adj[MN], des[MM*2], nxt[MM*2];
int stk[MN], cvis[MN];
std::bitset<MN>vis, pub;
bool saw_s, saw_p;
inline void add_edge(int u,int v) {
    des[ecnt] = v;
    nxt[ecnt] = adj[u];
    adj[u] = ecnt++;
}
void dfs1(int src) {
    vis[src] = 1;
    for(int i=adj[src]; ~i; i=nxt[i]) {
        if(!(i%2) || vis[des[i]]) continue;
        dfs1(des[i]);
    }
    stk[++stk[0]] = src;
}
int dfs2(int src) {
    int ret = 0;
    tot[ccnt] += val[src];
    val[src] = ccnt;
    vis[src] = 1;
    if(src == S) saw_s = 1;
    if(pub[src]) saw_p = 1;
    for(int i=adj[src]; ~i; i=nxt[i]) {
        if(i%2) continue;
        if(vis[des[i]]) {
            // Add the value if this is the first time we've seen it,
            // and is in different SCC
            if(val[des[i]] != ccnt && cvis[val[des[i]]] < ccnt) {
                ret = std::max(ret, tot[val[des[i]]]);
                cvis[val[des[i]]] = ccnt;
            }
            continue;
        }
        ret = std::max(ret, dfs2(des[i]));
    }
    return ret;
}
int main() {
    scanf("%d%d", &N, &M);
    memset(adj, -1, sizeof adj);
    for(int i=0,a,b; i<M; ++i) {
        scanf("%d%d", &a, &b);
        // edge from a -> b
        add_edge(a, b);
        add_edge(b, a);
    }
    for(int i=1;i<=N;++i)
        scanf("%d", &val[i]);
    scanf("%d%d", &S, &P);
    for(int i=0,a; i<P; ++i) {
        scanf("%d", &a);
        pub[a] = 1;
    }
    // do Kosaraju
    for(int i=1;i<=N;++i) {
        if(!vis[i]) dfs1(i);
    }
    vis.reset();
    while(stk[0]) {
        int u = stk[stk[0]--];
        if(!vis[u]) {
            int mx = dfs2(u);
            if(!saw_p && !mx) tot[ccnt] = 0;
            else tot[ccnt] += mx;
            if(saw_s) {
                printf("%d\n", tot[ccnt]);
                return 0;
            }
            ccnt += 1;
            saw_p = 0;
        }
    }
    assert(0);
}
