#include <stdio.h>

#define toL (ind << 1)
#define toR (toL | 1)
#define sl(i) segtree[i].l
#define sr(i) segtree[i].r
#define slz(i) segtree[i].lazy
#define sv(i) segtree[i].v
#define d(i) (segtree[i].r - segtree[i].l + 1)

struct seg {
    int l, r, v, lazy;
} segtree[600004];

int M, N, Q, A[200004];

void build(int ind, int left, int right) {
    sl(ind) = left;
    sr(ind) = right;
    slz(ind) = 0;
    if(left ^ right) {
        int mid = left + right >> 1;
        build(toL, left, mid);
        build(toR, mid + 1, right);
        sv(ind) = (sv(toL) % M + sv(toR) % M) % M;
    }else {
        sv(ind) = A[left] % M;
    }
}

void pushdown(int ind) {
    if(sl(ind) ^ sr(ind)) {
        sv(toL) = (sv(toL) + slz(ind) % M * d(toL) % M) % M;
        sv(toR) = (sv(toR) + slz(ind) % M* d(toR) % M) % M;
        slz(toL) = (slz(toL) % M + slz(ind) % M) % M;
        slz(toR) = (slz(toR) % M + slz(ind) % M) % M;
    }
    slz(ind) = 0;
}

void update(int ind, int left, int right, int x) {
    int l = sl(ind), r = sr(ind);
    if(left == l && right == r) {
        sv(ind) = (sv(ind) + x*d(ind) % M) % M;
        slz(ind) += x;
        return;
    }
    if(slz(ind)) pushdown(ind);
    int mid = l + r >> 1;
    if(right <= mid) {
        update(toL, left, right, x);
    }else if (left > mid) {
        update(toR, left, right, x);
    }else {
        update(toL, left, mid, x);
        update(toR, mid + 1, right, x);
    }
    sv(ind) = (sv(toL) + sv(toR)) % M;
}

int query(int ind, int left, int right) {
    int l = sl(ind), r = sr(ind);
    if(left == l && right == r) return sv(ind) % M;
    if(slz(ind)) pushdown(ind);
    int mid = l + r >> 1;
    if(right <= mid) return query(toL, left, right) % M;
    else if(left > mid) return query(toR, left, right) % M;
    else return (query(toL, left, mid) + query(toR, mid + 1, right)) % M;
}

int main() {
    scanf("%d%d%d", &M, &N, &Q);
    for(int i=1;i<=N;i++) {
        scanf("%d", &A[i]);
    }
    build(1, 1, N);
    for(int i=0;i<Q;i++) {
        int cmd;
        scanf("%d", &cmd);
        if(cmd ^ 2) {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            x %= M;
            update(1, l, r, x);
            /*
            for(int i=1;i<=(N << 1);i++) {
                printf("Segment: %d %d %d %d\n", sl(i), sr(i), sv(i), slz(i));
            }
            */
        }else {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", query(1, l, r));
        }
    }
}
