#include <bits/stdc++.h>
#define allOf(v) (v).begin(), (v).end()
typedef std::pair<int, int> pii;
const int MN = 2004;
int N, cnt, prev_dist, ret[MN];
pii pts[MN], upd[MN*MN];
std::vector<pii> edges;
int SQ(int i) { return i * i; }
int dist(int a, int b) {
    return SQ(pts[a].first - pts[b].first) + SQ(pts[a].second - pts[b].second);
}
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &pts[i].first, &pts[i].second);
    }
    for (int i = 0; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.emplace_back(i, j);
        }
    }
    std::sort(allOf(edges), [=](const pii &p1, const pii &p2) {
            return dist(p1.first, p1.second) < dist(p2.first, p2.second);
        });
    for (auto &e : edges) {
        int cur_dist = dist(e.first, e.second);
        if (cur_dist != prev_dist) {
            for (int i = 0; i < cnt; ++i) {
                ret[upd[i].first] = std::max(ret[upd[i].first], upd[i].second);
            }
            cnt = 0;
            prev_dist = cur_dist;
        }
        upd[cnt++] = {e.first, ret[e.second] + 1};
        if (e.first) {
            upd[cnt++] = {e.second, ret[e.first] + 1};
        }
    }
    for (int i = 0; i < cnt; ++i) {
        ret[upd[i].first] = std::max(ret[upd[i].first], upd[i].second);
    }
    printf("%d\n", ret[0]);
}
