#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> i3;
const int MAXN = 300004, MAXLN = 20;;

int N, cur[MAXN], par[MAXN], depth[MAXN], st[MAXN][MAXLN];
vector<int>adj[MAXN];
vector<i3>queries;
char c;

template<typename T1, typename T2>
void operator += (vector<T1> &v, T2 t) {
    v.emplace_back(t);
}

void dfs(int src, int p, int d = 0) {
    st[src][0] = p;
    depth[src] = d;
    for(int i:adj[src])
        if(i ^ p)
            dfs(i, src, d + 1);
}

void build() {
    dfs(0, -1);
    for(int j=1;j<MAXLN;++j)
        for(int i=0;i<=N;++i)
            if(~st[i][j-1])
                st[i][j] = st[st[i][j-1]][j-1];
            else
                st[i][j] = -1;
}

int query(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    for(int i=MAXLN-1;i>=0;--i)
        if(~st[u][i] && depth[st[u][i]] >= depth[v])
            u = st[u][i];
    if(u == v) return u;
    for(int i=MAXLN-1;i>=0;--i)
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    return st[u][0];
}

int main () {
    scanf("%d", &N);
    for(int i=1, a, b;i<=N;++i) {
        scanf(" %c", &c);
        switch(c) {
            case 'a':
                scanf("%d", &a);
                par[i] = cur[a];
                adj[cur[a]] += i;
                cur[i] = i;
                break;
            case 'b':
                scanf("%d", &a);
                queries += make_tuple(0, cur[a], 0);
                cur[i] = par[cur[a]];
                adj[par[a]] += i;
                break;
            case 'c':
                scanf("%d%d", &a, &b);
                cur[i] = cur[a];
                adj[par[cur[a]]] += i;
                queries += make_tuple(1, cur[a], cur[b]);
                break;
        }
    }
    build();
    for(i3 &t:queries)
        if(get<0>(t))
            printf("%d\n", depth[query(get<1>(t), get<2>(t))]);
        else
            printf("%d\n", get<1>(t));
}
