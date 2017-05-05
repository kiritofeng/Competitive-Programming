#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()

struct edge {
    int src, des, dis;

    //Whoops forgot to create a less than operator
    bool operator <(const edge &e) const {
        return dis < e.dis;
    }
};

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN=50004, RT=230;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int N, M, cnt, max_edge, lca, ds[MAXN], depth[MAXN], par[MAXN], jpar[MAXN], maxedge[MAXN], jmaxedge[MAXN];
ll mst, ans = INF;
vector<edge>edges, rem;
vector<pii>adj[MAXN];

void init() {
    for(int i=1;i<=N;i++) ds[i] = i;
}

int find(int x) {
    return ds[x] = (ds[x] == x ? x : find(ds[x]));
}

bool merge(int x, int y) {
    int xr = find(x), yr = find(y);
    if(xr ^ yr)
        return ds[xr] = yr;
    return 0;
}

//Fuck HLD
void dfs(int src=1, int pre=-1, int preedge=0, int d=0) {
    depth[src] = d;
    par[src] = pre;
    maxedge[src] = preedge;
    //You jump to the bottom one
    if(d%RT) {
        jpar[src] = jpar[pre];
        jmaxedge[src] = max(jmaxedge[pre], preedge);
    } else {
        jpar[src] = pre;
        jmaxedge[src] = preedge;
    }
    for(pii p: adj[src])
        if(p.first ^ pre)
            dfs(p.first, src, p.second, d+1);
}

int find_lca(int x, int y) {
    while(jpar[x] ^ jpar[y]) {
        if(depth[x] < depth[y]) swap(x, y);
        x = jpar[x];
    }
    while(x ^ y) {
        if(depth[x] < depth[y]) swap(x, y);
        x = par[x];
    }
    return x;
}

int find_max_edge(int x, int y) {
    int ret = 0;
    while(~jpar[x] && depth[jpar[x]] >= depth[y]) {
        ret = max(ret, jmaxedge[x]);
        x = jpar[x];
    }
    while(x ^ y) {
        ret = max(ret, maxedge[x]);
        x = par[x];
    }
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    for(int i=0, a, b, c;i<M;i++) {
        scanf("%d%d%d", &a, &b, &c);
        edges.push_back({a, b, c});
    }
    //Why do I keep forgetting this
    init();
    sort(all(edges));
    //Kruskal
    for(auto e: edges)
        if(merge(e.src, e.des)) {
            adj[e.src].push_back({e.des, e.dis});
            adj[e.des].push_back({e.src, e.dis});
            mst += e.dis;
        } else
            rem.push_back(e);
    //Process the MST
    dfs();
    for(auto e:rem) {
        lca = find_lca(e.src, e.des);
        max_edge = max(find_max_edge(e.src, lca), find_max_edge(e.des, lca));
        if(e.dis>max_edge)
            ans = min(ans, mst - max_edge + e.dis);
    }
    if(ans == INF || N - 1 > M)
        puts("-1");
    else
        printf("%lld", ans);
}
