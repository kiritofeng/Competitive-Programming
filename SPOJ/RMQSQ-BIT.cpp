#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100004, INF = 0x3f3f3f3f;
int N, Q, A[MAXN], bit[MAXN];

inline void update(int ind, int val) {
    for(;ind<MAXN;ind+=ind&-ind)
        bit[ind] = min(bit[ind], val);
}

inline int query(int left, int right) {
    int res = INF;
    for(;right>=left;)
        if(right-(right&-right)+1>=left) {
            res = min(res, bit[right]);
            right-=right&-right;
        } else {
            res = min(res, A[right]);
            --right;
        }
    return res;
}

int main() {
    scanf("%d", &N);
    memset(bit, 0x3f, sizeof bit);
    for(int i=1;i<=N;++i) {
        scanf("%d", A+i);
        update(i, A[i]);
    }
    scanf("%d", &Q);
    for(int i=0, l, r;i<Q;++i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l+1, r+1));
    }
}
