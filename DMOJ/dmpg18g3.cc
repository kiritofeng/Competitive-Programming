#include <bits/stdc++.h>
#define allOf(v) (v).begin(), (v).end()
typedef long long ll;
typedef std::pair<int, int> pii;
const int MN = 2e5+4, MQ = 2e5+4;
int N, Q, psa_d[MN], idx[MQ];
int tcnt, par[MN], hvy[MN], sz[MN], depth[MN], tin[MN], tout[MN], tid[MN];
ll ans[MN], psa_q[MQ];
std::vector<int> adj[MN];
std::vector<pii> qrys[MN];
int bit[MN];

ll SQ(int i) { return 1LL * i * i; }

int qry(int i) {
  int ret = 0;
  for (; i; i -= i & -i) { ret += bit[i]; }
  return ret;
}

void mod(int i, int v) {
  for (; i <= N; i += i & -i) { bit[i] += v; }
}

void dfs1(int u, int p) {
  depth[u] = depth[p] + 1;
  hvy[u] = -1;
  sz[u] = 1;
  tid[tin[u] = ++tcnt] = u;

  for (int v : adj[u]) {
    if (v == p) { continue; }
    dfs1(v, u);
    if (hvy[u] == -1 || sz[v] > sz[hvy[u]]) { hvy[u] = v; }
  }
  tout[u] = tcnt;
}

void dfs2(int u, int p, bool clear=0) {
  for (int v : adj[u]) {
    if (v == p || v == hvy[u]) { continue; }
    dfs2(v, u, 1);
  }
  if (hvy[u] != -1) { dfs2(hvy[u], u, 0); }

  for (const auto &q : qrys[u]) {
    ans[q.second] -= SQ(qry(q.first));
  }

  for (int i : adj[u]) {
    if (i == p || i == hvy[u]) { continue; }
    int max_d = depth[u];
    for (int j = tin[i]; j <= tout[i]; ++j) {
      int v = tid[j];
      psa_d[depth[v]] += 1;
      mod(depth[v], 1);
      max_d = std::max(max_d, depth[v]);
    }
    int last_q = 0;
    for (int j = depth[u]+1; j <= max_d; ++j) {
      psa_d[j] += psa_d[j-1];
      while (last_q < qrys[u].size() && qrys[u][last_q].first < j) { ++last_q; }
      while (last_q < qrys[u].size() && qrys[u][last_q].first == j) {
        ans[qrys[u][last_q].second] -= SQ(psa_d[j]);
        ++last_q;
      }
    }
    if (last_q < qrys[u].size()) { psa_q[last_q] += SQ(psa_d[max_d]); }
    for (int j = depth[u] + 1; j <= max_d; ++j) {
      psa_d[j] = 0;
    }
  }

  for (int i = 0; i < qrys[u].size(); ++i) {
    if (i > 0) { psa_q[i] += psa_q[i-1]; }
    ans[qrys[u][i].second] -= psa_q[i];
  }
  for (int i = 0; i < qrys[u].size(); ++i) { psa_q[i] = 0; }

  for (const auto &q : qrys[u]) {
    int qry_ret = qry(q.first);
    ans[q.second] = (ans[q.second] + SQ(qry_ret)) / 2;
    ans[q.second] += qry_ret + 1;
  }
  mod(depth[u], 1);

  if (clear) {
    for (int i = tin[u]; i <= tout[u]; ++i) {
      int v = tid[i];
      mod(depth[v], -1);
    }
  }
}

int main() {
  scanf("%d", &N);
  for (int i = 1, a, b; i < N; ++i) {
    scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs1(1,0);

  scanf("%d", &Q);
  for (int i = 0, a, b; i < Q; ++i) {
    scanf("%d%d", &a, &b);
    qrys[a].emplace_back(std::min(b + depth[a], N), i);
  }
  memset(idx, -1, sizeof idx);
  for (int u = 1; u <= N; ++u) {
    std::sort(allOf(qrys[u]));
    qrys[u].erase(std::unique(allOf(qrys[u]), [=](const pii &p1, const pii &p2) {
        if (p1.first == p2.first) {
            idx[p2.second] = p1.second;
            return 1;
        }
        return 0;
    }), qrys[u].end());
  }

  dfs2(1, 0);

  for (int i = 0; i < Q; ++i) {
    printf("%lld\n", ans[idx[i] == -1 ? i : idx[i]]);
  }
}
