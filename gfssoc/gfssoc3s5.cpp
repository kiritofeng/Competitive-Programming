#include <bits/stdc++.h>

using namespace std;

#define toL ind << 1
#define toR toL | 1
#define sl(x) segtree[x].l
#define sr(x) segtree[x].r
#define sv(x) segtree[x].v

const int MAXN = 100004; 

int N, Q, A[MAXN];

struct seg {
    int l, r, v[4];
    /**
     * v[0] is left
     * v[1] is right
     * v[2] is total
     * v[3] is best
     */
}segtree[MAXN << 2];

void best(int ind) {
    sv(ind)[0] = max(sv(toL)[0], sv(toL)[2] | sv(toR)[0]);
    sv(ind)[1] = max(sv(toR)[1], sv(toL)[1] | sv(toR)[2]);
    sv(ind)[2] = sv(toL)[2] | sv(toR)[2];
    sv(ind)[3] = max({sv(ind)[0], sv(ind)[1], sv(ind)[2], sv(toL)[1] | sv(toR)[0], sv(toL)[3], sv(toR)[3]});
}

void build(int left = 1, int right = N, int ind = 1) {
    sl(ind) = left;
    sr(ind) = right;
    if(left ^ right) {
        int mid = left + right >> 1;
        build(left, mid, toL);
        build(mid + 1, right, toR);
        best(ind);
    } else
        sv(ind)[0] = sv(ind)[1] = sv(ind)[2] = sv(ind)[3] = A[left];
}

void update(int pos, int val, int ind = 1) {
    if(sl(ind) ^ sr(ind)) {
        int mid = sl(ind) + sr(ind) >> 1;
        if(pos <= mid)
            update(pos, val, toL);
        else
            update(pos, val, toR);
        best(ind);
    } else
        sv(ind)[0] = sv(ind)[1] = sv(ind)[2] = sv(ind)[3] = val;
}

int main() {
    scanf("%d%d", &N, &Q);
    for(int i=1;i<=N;i++)
        scanf("%d", &A[i]);
    build();
    for(int i=0, a, b;i<Q;i++) {
        scanf("%d%d", &a, &b);
        update(a, b);
        printf("%d\n", sv(1)[3]);
    }
}
