#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100004, INF = 0x3f3f3f3f;
int N, Q, st[MAXN<<1];

inline void build() {
    for(int i=N-1;i;--i) st[i] = min(st[i<<1],st[i<<1|1]);
}

inline int query(int l, int r) {
    int res = INF;
    for(l+=N,r+=N;l<r;l>>=1,r>>=1) {
        if(l&1) res = min(res, st[l++]);
        if(r&1) res = min(res, st[--r]);
    }
    return res;
}

int main() {
    scanf("%d", &N);
    for(int i=0;i<N;++i)
        scanf("%d", st+N+i);
    build();
    scanf("%d", &Q);
    for(int i=0, l, r;i<Q;++i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r+1));
    }
}
