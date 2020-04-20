#include<bits/stdc++.h>
#define allOf(v) v.begin(), v.end()
typedef long long ll;
typedef std::pair<int,int>pii;
typedef std::pair<int,ll>pil;
const int MN = 5e5+4;
const ll INF = 0x3f3f3f3f3f3f3f3f;
std::vector<pii>adj[MN];
std::vector<pil>vadj[MN];
std::vector<int>to_clear;
int ecnt,eid[MN],ein[MN];
int sz[MN],hvy[MN],par[MN],top[MN],depth[MN];
ll len[MN];
int stk[MN];
bool isX[MN],isY[MN];
ll d1[MN], d2[MN], ret[MN];
inline void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}
inline void add_vedge(int u, int v) {
    to_clear.push_back(u);
    to_clear.push_back(v);
    ll w = abs(len[u] - len[v]);
    vadj[u].push_back({v, w});
    vadj[v].push_back({u, w});
}
void dfs1(int u=0, int p=-1, int d=0) {
    par[u] = p;
    depth[u] = d;
    sz[u] = 1;
    hvy[u] = -1;
    for(pii e : adj[u]) {
        if(e.first == p) continue;
        len[e.first] = len[u] + e.second;
        dfs1(e.first, u, d+1);
        sz[u] += sz[e.first];
        if(!~hvy[u] || sz[e.first] > sz[hvy[u]]) hvy[u] = e.first;
    }
}
void dfs2(int u=0, int t=0) {
    top[u] = t;
    eid[ein[u] = ++ecnt] = u;
    if(~hvy[u]) dfs2(hvy[u], t);
    for(pii e : adj[u]) {
        if(e.first == par[u] || e.first == hvy[u]) continue;
        dfs2(e.first, e.first);
    }
}
inline int lca(int u, int v) {
    while(top[u] != top[v]) {
        if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
        u = par[top[u]];
    }
    return depth[u] < depth[v] ? u : v;
}
void Init(int N, int A[], int B[], int D[]) {
    for(int i=0;i<N-1;++i)
        add_edge(A[i], B[i], D[i]);
    dfs1();
    dfs2();
}
void dfs3(int u, int p) {
    d1[u] = d2[u] = ret[u] = INF;
    if(isX[u]) d1[u] = 0;
    if(isY[u]) d2[u] = 0;
    for(auto a : vadj[u]) {
        if(a.first == p) continue;
        dfs3(a.first, u);
        d1[u] = std::min(d1[u], a.second + d1[a.first]);
        d2[u] = std::min(d2[u], a.second + d2[a.first]);
        ret[u] = std::min(ret[u], ret[a.first]);
    }
    ret[u] = std::min(ret[u], d1[u] + d2[u]);
}
int F[MN];
ll Query(int S, int X[], int T, int Y[]) {
    for(int i=0;i<S;++i) {
        F[i] = X[i];
        isX[X[i]] = 1;
    }
    for(int i=0;i<T;++i) {
        F[i+S] = Y[i];
        isY[Y[i]] = 1;
    }
    std::sort(F, F + S + T, [=](const int &a, const int &b) {
            return ein[a] < ein[b];
            });
    stk[0] = 0;
    for(int i=0;i<S+T;++i) {
        if(!stk[0]) stk[++stk[0]] = F[i];
        else {
            int l = lca(stk[stk[0]], F[i]);
            if(l == stk[stk[0]]) stk[++stk[0]] = F[i];
            else {
                while(stk[0] > 1 && depth[stk[stk[0]-1]] >= depth[l]) {
                    add_vedge(stk[stk[0]], stk[stk[0] - 1]);
                    --stk[0];
                }
                if(stk[stk[0]] != l) {
                    add_vedge(l, stk[stk[0]]);
                    stk[stk[0]] = l;
                }
                stk[++stk[0]] = F[i];
            }
        }
    }
    while(stk[0] > 1) {
        add_vedge(stk[stk[0] - 1], stk[stk[0]]);
        --stk[0];
    }
    #ifdef DEBUG
        print_vtree();
    #endif
    dfs3(F[0],-1);
    for(int i : to_clear) {
        vadj[i].clear();
        isX[i] = isY[i] = 0;
    }
    to_clear.clear();
    return ret[F[0]];
}
#ifndef SIGNATURE_GRADER
int _N,_Q,_A[MN],_B[MN],_D[MN],_S,_T,_X[MN],_Y[MN];
int main() {
    scanf("%d%d",&_N,&_Q);
    for(int i=0;i<_N-1;++i) {
        scanf("%d%d%d",&_A[i],&_B[i],&_D[i]);
    }
    Init(_N, _A, _B, _D);
    for(int i=0;i<_Q;++i) {
        scanf("%d%d",&_S,&_T);
        for(int j=0;j<_S;++j)
            scanf("%d",&_X[j]);
        for(int j=0;j<_T;++j)
            scanf("%d",&_Y[j]);
        printf("%lld\n", Query(_S, _X, _T, _Y));
    }
}
#endif
