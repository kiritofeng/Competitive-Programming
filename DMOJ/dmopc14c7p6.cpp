#include <bits/stdc++.h>

using namespace std;

#define toL ind << 1
#define toR toL | 1
#define sl(x) st[x].l
#define sr(x) st[x].r
#define ss(x) st[x].sum
#define sb(x) st[x].best

int N, ans, A[100004];

struct seg {
    int l, r, sum, best;
}st[300004];

void build(int left=1, int right=N, int ind=1) {
    sl(ind) = left;
    sr(ind) = right;
    if(sl(ind) ^ sr(ind)) {
        int mid = left + right >> 1;
        build(left, mid, toL);
        build(mid + 1, right, toR);
    }
}

void update(int pos, int val, int ind=1) {
    if(sl(ind) ^ sr(ind)) {
        int mid = sl(ind) + sr(ind) >> 1;
        if(pos <= mid)
            update(pos, val, toL);
        else
            update(pos, val, toR);
        sb(ind) = max(sb(toL), ss(toL) + sb(toR));
        ss(ind) = ss(toL) + ss(toR);
    } else
        ss(ind) = sb(ind) = val;
}

int main() {
    scanf("%d", &N);
    for(int i=1;i<=N;i++)
        scanf("%d", &A[i]);
    build();
    for(int i=1;2*i<=N;i++) {
        update(A[i << 1], -1);
        update(A[(i << 1) - 1], -1);
        update(A[i], 1);
        if(sb(1) <= 0) ans = i;
    }
    printf("%d", ans);
}
