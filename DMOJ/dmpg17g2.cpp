#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 100004;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct sum {
    ll l, r, t, b;

    sum(ll x, ll y, ll z, ll w): l(x), r(y), t(z), b(w){}
};

sum best(sum l, sum r) {
    sum ret = sum(max(l.l, l.t + r.l), max(r.r, r.t + l.r), l.t + r.t, max({l.b, r.b, l.r + r.l}));
    ret.b = max({ret.l, ret.r, ret.t, ret.b});
    return ret;
}

struct seg {
    int l, r;
    sum s;

    seg(): l(0), r(0), s(sum(-INF, -INF, -INF, -INF)) {}

    seg(int ll, int rr): l(ll), r(rr), s(sum(-INF, -INF, -INF, -INF)) {}

} st[MAXN << 2];

#define toL ind << 1
#define toR toL | 1

int N, Q, x, y, A[MAXN];
char c;

void pushup(int ind) {
    st[ind].s = best(st[toL].s, st[toR].s);
}

void build(int left=1, int right=N, int ind=1) {
    if(left^right) {
        int mid = left + right >> 1;
        build(left, mid, toL);
        build(mid + 1, right, toR);
        st[ind] = seg(left, right);
        pushup(ind);
    } else {
        st[ind] = seg(left, right);
        st[ind].s = sum(A[left], A[left], A[left], A[left]);
    }
}

void update(int pos, int val, int ind=1) {
    if(st[ind].l^st[ind].r) {
        int mid = st[ind].l + st[ind].r >> 1;
        if(pos <= mid) update(pos, val, toL);
        else update(pos, val, toR);
        pushup(ind);
    } else {
        st[ind].s = sum(val, val, val, val);
    }
}

sum query(int left, int right, int ind=1) {
    if(left == st[ind].l && right == st[ind].r)
        return st[ind].s;
    int mid = st[ind].l + st[ind].r >> 1;
    if(right <= mid) return query(left, right, toL);
    else if(left > mid) return query(left, right, toR);
    else return best(query(left, mid, toL), query(mid + 1, right, toR));
}

int main() {
    scanf("%d%d", &N, &Q);
    for(int i=1;i<=N;i++)
        scanf("%d", A + i);
    build();
    for(int i=0;i<Q;i++) {
        scanf(" %c%d%d", &c, &x, &y);
        if(c == 'S') update(x, y);
        else printf("%lld\n", query(x, y).b);
    }
}
