#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()

using namespace std;

typedef long long ll;

const int MAXN = 100004, MAXQ = 100004, RT = 316;

struct query {
    int i, l, r;
}queries[MAXQ];

bool cmp(const query &a, const query &b) {
    if(a.l / RT != b.l / RT)
        return a.l / RT < b.l / RT;
    return a.r < b.r;
}

int N, Q, l=1, r=1, c, pre = -1, cnt, A[MAXN];
ll sol, bit[MAXN], ans[MAXQ];
set<int>CA;
unordered_map<int, int>cmprs;

void update(int i, int v) {
    for(;i<=cnt;i += i & -i)
        bit[i]+=v;
}

ll freq(int i) {
    ll ret = 0;
    for(;i>0;i -= i & -i)
        ret += bit[i];
    return ret;
}

int main() {
    scanf("%d", &N);
    for(int i=1;i<=N;i++) {
        scanf("%d", &A[i]);
        CA.insert(A[i]);
    }
    for(int i:CA)
        cmprs[i] = ++cnt;
    for(int i=1;i<=N;i++)
        A[i] = cmprs[A[i]];
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;i++) {
        scanf("%d%d", &a, &b);
        queries[i] = {i, a, b};
    }
    sort(queries, queries + Q, cmp);
    for(int i=0;i<Q;i++) {
        if(queries[i].l/RT!=pre) {
            memset(bit, 0, sizeof bit);
            l=r=queries[i].l;
            update(A[queries[i].l], 1);
            sol=0;
            pre=queries[i].l/RT;
        }
        while(l < queries[i].l) {
            c = A[l++];
            sol -= freq(c - 1);
            update(c, -1);
        }
        while(r < queries[i].r) {
            c = A[++r];
            update(c, 1);
            sol += r - l + 1 - freq(c);
        }
        while(l > queries[i].l) {
            c = A[--l];
            update(c, 1);
            sol += freq(c - 1);
        }
        while(r > queries[i].r) {
            c = A[r--];
            update(c, -1);
            sol -= r - l + 1 - freq(c);
        }
        ans[queries[i].i] = sol;
    }
    for(int i=0;i<Q;i++)
        printf("%lld\n", ans[i]);
}
