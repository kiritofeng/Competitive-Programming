#include <bits/stdc++.h>

using namespace std;

#define r3mark god

#define lft ind << 1
#define rht ind << 1 | 1
#define sl(x) segtree[x].l
#define sr(x) segtree[x].r
#define sb(x) segtree[x].b
#define all(x) x.begin(), x.end()
#define elif else if

struct seg {
    int l, r;
    bitset<1000>b;
};

seg segtree[279004];
int N, Q, A[100004];
queue<int>aval;
unordered_map<int, int>remap, cnt;
bitset<1000>tmp;

void build(int ind=1, int left=1, int right=N) {
    sl(ind) = left;
    sr(ind) = right;
    if(left ^ right) {
        int mid = left + right >> 1;
        build(lft, left, mid);
        build(rht, mid + 1, right);
        sb(ind) = sb(lft) | sb(rht);
    } else
        sb(ind).set(remap[A[left]]);
}

void update(int ind, int pos, int val, int old) {
    if(sl(ind) ^ sr(ind)) {
        int mid = sl(ind) + sr(ind) >> 1;
        if(pos <= mid) update(lft, pos, val, old);
        else update(rht, pos, val, old);
        sb(ind) = sb(lft) | sb(rht);
    } else {
        sb(ind).reset(remap[old]);
    }
    sb(ind).set(remap[val]);
}

void query(int ind, int left, int right) {
    if(sl(ind) == left && sr(ind) == right) {
        tmp |= sb(ind);
    } else {
        int mid = sl(ind) + sr(ind) >> 1;
        if(right <= mid)
            query(lft, left, right);
        elif(left > mid)
            query(rht, left, right);
        else {
            query(lft, left, mid);
            query(rht, mid + 1, right);
        }
    }
}

int main() {
    scanf("%d%d", &N, &Q);
    for(int i=0;i<=1000;i++)
        aval.push(i);
    for(int i=1;i<=N;i++) {
        scanf("%d", &A[i]);
        if(!cnt[A[i]]) {
            remap[A[i]] = aval.front();
            aval.pop();
        }
        cnt[A[i]]++;
    }
    build();
    for(int i=0, a, b, c;i<Q;i++) {
        scanf("%d%d%d", &a, &b, &c);
        if(a & 1) {
            if(!cnt[c]) {
                remap[c] = aval.front();
                aval.pop();
            }
            update(1, b, c, A[b]);
            cnt[A[b]]--;
            if(!cnt[A[b]])
                aval.push(remap[A[b]]);
            cnt[c]++;
            A[b] = c;
        } else {
            query(1, b, c);
            printf("%d\n", tmp.count());
            tmp.reset();
        }
    }
}
