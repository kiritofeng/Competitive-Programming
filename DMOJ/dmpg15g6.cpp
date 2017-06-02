#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
#define all(x) x.begin(), x.end()
const int MAXN = 200004, RT = 440;
int N, M, Q, L, A[MAXN], cnt[MAXN];
vector<int>app[MAXN];
queue<int>vis;
pii F[MAXN];

bool cmp(const pii &a, const pii &b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}

bool bf(int a, int b, int i) {
    int G = 0;
    for(int j=a;j<=b;j++) {
        ++cnt[A[j]];
        vis.push(A[j]);
    }
    while(!vis.empty()) {
        int cur = vis.front();
        vis.pop();
        G += (3LL * cnt[cur] >= L) + (3LL * cnt[cur] >= 2LL * L);
        cnt[cur] = 0;
    }
    return G >= 2;
}

bool good(int a, int b) {
    int G = 0, dist = 0;
    for(int j=0;j<M;j++)
        if(F[j].second >= RT) {
            dist = upper_bound(all(app[F[j].first]), b) - lower_bound(all(app[F[j].first]), a);
            G += (3LL * dist >= L) + (3LL * dist >= 2LL * L);
        } else
            break;
    return G >= 2;
}

int main() {
    scanf("%d%d", &N, &M);
    for(int i=0;i<=M;i++)
        F[i].first = i;
    for(int i=1;i<=N;i++) {
        scanf("%d", &A[i]);
        ++F[A[i]].second;
        app[A[i]].push_back(i);
    }
    sort(F, F + M + 1, cmp);
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;i++) {
        scanf("%d%d", &a, &b);
        L = b - a + 1;
        if(L <= 3LL * RT) {
            if(bf(a, b, i)) puts("YES");
            else puts("NO");
        } else {
            if(good(a, b)) puts("YES");
            else puts("NO");
        }
    }
}
