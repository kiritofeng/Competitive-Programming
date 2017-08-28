#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+4, MAXQ = 1e4 + 4, RT = 316, INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
typedef tuple<int, int, int> t3i;
int N, Q, ans[MAXQ], A[MAXN];
t3i q[MAXQ];
priority_queue<pii, vector<pii>, greater<pii>>pq;
int main() {
    scanf("%d", &N);
    for(int i=0;i<N;scanf("%d", A + i++));
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;++i) {
        scanf("%d%d", &a, &b);
        q[i] = {i, a, b};
    }
    sort(q, q + Q, [](const t3i &t1, const t3i &t2){
         return get<1>(t1)/RT<get<1>(t2)/RT||(get<1>(t1)/RT==get<1>(t2)/RT&&get<2>(t1)<get<2>(t2));
    });
    for(int i=0, l=-1, r=-1;i<Q;++i) {
        while(r<get<2>(q[i]))
            ++r, pq.push({A[r], r});
        while(l>get<1>(q[i]))
            --l, pq.push({A[l], l});
        while(r>get<2>(q[i]))
            --r;
        while(l<get<1>(q[i]))
            ++l;
        while(pq.top().second < get<1>(q[i]) || pq.top().second > get<2>(q[i]))
            pq.pop();
        ans[get<0>(q[i])] = pq.top().first;
    }
    for(int i=0;i<Q;printf("%d\n", ans[i++]));
}
