#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100004, RT = 320;
int N, Q, cnt, ln, depth[MAXN], tin[MAXN], par[MAXN], jpar[MAXN];
vector<int>adj[MAXN];
set<int>oc[MAXN];

template<typename T>
void operator += (vector<T> &v, T t) {
    v.push_back(t);
}

void dfs(int src=1, int pre=-1, int d = 0) {
    par[src] = pre;
    if(d % RT) jpar[src] = jpar[pre];
    else jpar[src] = par[src];
    depth[src] = d;
    tin[src] = cnt;
    oc[src].insert(cnt++);
    for(int i:adj[src])
        if(i ^ pre) {
            dfs(i, src, d + 1);
            oc[src].insert(cnt++);
        }
}

void init() {
    cnt = 0;
    dfs();
}

int LCA(int x, int y) {
    while(jpar[x]^jpar[y]) {
        if(depth[x] < depth[y]) swap(x, y);
        x = jpar[x];
    }
    while(x ^ y) {
        if(depth[x] < depth[y]) swap(x, y);
        x = par[x];
    }
    return x;
}

int main() {
    scanf("%d", &N);
    for(int i=1, jj;i<=N;i++) {
        scanf("%d", &jj);
        for(int j=0, a;j<jj;j++) {
            scanf("%d", &a);
            adj[i] += a;
        }
    }
    init();
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;i++) {
        scanf("%d%d", &a, &b);
        if(a == b) {
            puts("0");
            continue;
        }
        int l = LCA(a, b);
        if(tin[a] < tin[b])
            printf("%d\n", tin[b] - tin[l] - (depth[a] - depth[l]));
        else {
            int sum = 0;
            auto it = oc[l].lower_bound(tin[a]);
            if(*it != tin[a]) {
                sum = *it;
                --it;
                sum -= *it;
            }
            printf("%d\n", tin[b] - tin[l] + sum - (depth[a] - depth[l]));
        }
    }
}
