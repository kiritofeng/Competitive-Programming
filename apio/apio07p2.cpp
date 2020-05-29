#include <bits/stdc++.h>
#include <bits/extc++.h>
typedef long long ll;
typedef std::pair<int, int> pii;
const int MN=1e5+4;
int N, K, ans, S[MN];
int pre[MN], nxt[MN], pre_v[MN], nxt_v[MN];
__gnu_pbds::priority_queue<std::pair<int, pii>, std::greater<std::pair<int, pii>>> pq;
std::bitset<MN> vis;
int main() {
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i) {
        scanf("%d", &S[i]);
        pre[i] = i - 1;
        nxt[i] = i + 1;
        if(i) {
            pq.push({S[i] - S[i-1], {i-1, i}});
            pre_v[i] = nxt_v[i-1] = S[i] - S[i-1];
        }
    }
    for(int cnt=0; cnt<K;) {
        auto cur = pq.top();
        pq.pop();
        int l = cur.second.first, r = cur.second.second;
        if(vis[l] || vis[r]) continue;
        ans += cur.first;
        vis[l] = vis[r] = 1;
        ++cnt;
        if(pre[l] == -1 || nxt[r] == N) continue;
        nxt[pre[l]] = nxt[r];
        pre[nxt[r]] = pre[l];
        int val = nxt_v[r] + pre_v[l] - cur.first;
        nxt_v[pre[l]] = pre_v[nxt[r]] = val;
        pq.push({val, {pre[l], nxt[r]}});
    }
    printf("%d\n", ans);
}
