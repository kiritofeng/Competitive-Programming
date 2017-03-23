#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 18;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int N, M;
ll ans, adj[MAXN][MAXN];
ll memo[MAXN][1 << MAXN];

bool check_bit(int mask, int ind) {
    return mask & (1 << ind);
}

int set_bit(int mask, int ind) {
    return mask | (1 << ind);
}

int clear_bit(int mask, int ind) {
    return mask & ~(1 << ind);
}

ll dp(int src, int vis) {
    if(memo[src][vis] ^ -1) return memo[src][vis];
    if(src == N - 1) return memo[src][vis] = 0;
    vis = set_bit(vis, src);
    int tmp = memo[src][vis] = -INF;
    for(int i=0;i<N;i++)
        if(adj[src][i] ^ -1  && !check_bit(vis, i)) {
            tmp = dp(i, set_bit(vis, i));
            if(tmp ^ -INF)
                memo[src][vis] = max(memo[src][vis], tmp + adj[src][i]);
        }
    return memo[src][vis];
}

int main() {
    scanf("%d%d", &N, &M);
    memset(memo, -1, sizeof memo);
    memset(adj, -1, sizeof adj);
    for(ll i=0, a, b, c;i<M;i++) {
        scanf("%lld%lld%lld", &a, &b, &c);
        adj[a][b] = max(adj[a][b], c);
    }
    printf("%lld", dp(0, 0));
}
