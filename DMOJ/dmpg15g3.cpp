#include<bits/stdc++.h>
#define allOf(v) v.begin(), v.end()
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::vector<pii> vii;
const int MN = 2e5 + 4;
int N, LK, RK, LC, RC;
char S[MN];
std::vector<int>adj[MN];
int sz[MN];
bool vis[MN];
ll bit[MN];
void dfs1(int u=1, int p=0) {
    sz[u] = 1;
    for(int i : adj[u]) {
        if(i == p || vis[i]) continue;
        dfs1(i, u);
        sz[u] += sz[i];
    }
}
int find_cen(int u, int p, int s) {
    for(int i : adj[u]) {
        if(i == p || vis[i]) continue;
        if(2 * sz[i] <= s) continue;
        return find_cen(i, u, s);
    }
    return u;
}
void dfs2(int u, int p, vii &tmp, int k=0, int c=0) {
    k += S[u] == 'K';
    c += S[u] == 'C';
    tmp.push_back({k, c});
    for(int i : adj[u]) {
        if(vis[i] || i == p) continue;
        dfs2(i, u, tmp, k, c);
    }
}
inline void mod(int ind,int val) {
    for(;ind < MN; ind += ind & -ind)
        bit[ind] += val;
}
inline ll qry(int ind) {
    ll ret = 0;
    for(;ind > 0; ind -= ind & -ind)
        ret += bit[ind];
    return ret;
}
inline ll count(int K, int C, vii &v) {
    if(K < 0 || C < 0) return 0;
    ll ret = 0;
    int l = 0, r = v.size() - 1;
    for(;r >= 0; --r) {
        if(v[r].first * 2 <= K && v[r].second * 2 <= C) ret -= 1; // don't double count
        for(;l < v.size() && v[r].first + v[l].first <= K; ++l)
            mod(v[l].second + 1, 1);
        ret += qry(C - v[r].second + 1);
    }
    for(int i = 0; i < l; ++i)
        mod(v[i].second + 1, -1);
    return ret;
}
inline ll count(pii cur, vii &v) {
    std::sort(allOf(v));
    return count(RK - cur.first, RC - cur.second, v) - count(RK - cur.first, LC - cur.second - 1, v) - count(LK - cur.first - 1, RC - cur.second, v) + count(LK - cur.first - 1, LC - cur.second - 1, v);
}
ll solve(int u=1) {
    ll ret = 0;
    dfs1(u, 0);
    int c = find_cen(u, u, sz[u]);
    vis[c] = 1;
    pii cur = {S[c] == 'K', S[c] == 'C'};
    vii all;
    all.push_back({0, 0});
    for(int i : adj[c]) {
        vii tmp;
        if(vis[i]) continue;
        dfs2(i, c, tmp);
        ret -= count(cur, tmp);
        all.insert(all.end(), allOf(tmp));
    }
    ret += count(cur, all);
    // c isn't included by count
    if(LK <= cur.first && cur.first <= RK && LC <= cur.second && cur.second <= RC) ret += 2;
    ret /= 2;
    for(int i : adj[c]) {
        if(vis[i]) continue;
        ret += solve(i);
    }
    return ret;
}
int main() {
    scanf("%d%d%d%d%d",&N,&LK,&RK,&LC,&RC);
    scanf("%s",S+1);
    for(int i = 1, a, b; i < N; ++i) {
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    printf("%lld\n", solve());
}
