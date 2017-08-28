#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+4, MAXQ = 1e4 + 4, INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
typedef tuple<int, int, int> t3i;
int N, Q, A[MAXN], ans[MAXQ];
t3i q[MAXQ];
deque<pii>dq;
int main() {
    scanf("%d", &N);
    for(int i=0;i<N;scanf("%d", A+i++));
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;++i) {
        scanf("%d%d", &a, &b);
        q[i] = {i, a, b};
    }
    sort(q, q+Q, [](const t3i &t1, const t3i &t2){
         return get<1>(t1) > get<1>(t2) || (get<1>(t1) == get<1>(t2) && get<2>(t1) < get<2>(t2));
    });
    for(int i=0,pt=N;i<Q;++i) {
        while(pt >= get<1>(q[i])) {
            while(!dq.empty() && A[pt] <= dq.front().second)
                dq.pop_front();
            dq.push_front({pt, A[pt]});
            --pt;
        }
        ans[get<0>(q[i])] = prev(upper_bound(dq.begin(), dq.end(), make_pair(get<2>(q[i])+1, -INF))) -> second;
    }
    for(int i=0;i<Q;printf("%d\n", ans[i++]));
}
