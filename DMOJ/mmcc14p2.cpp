#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2004, MAXM = 5004, RT = 50, seed1 = 3, mod1 = 1000000007;

int N, M, Q, R[MAXN], S[RT], H[MAXN][MAXM];
char tmp[MAXM];

void hashify(int ind) {
    for(int i=1;i<=M;i++) {
        H[ind][i] = ((tmp[i - 1] - '0') % mod1 + H[ind][i - 1] * seed1 % mod1) % mod1;
    }
}

int bin(int i, int j, int hi) {
    int lo = 0, mid, ret = 0;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        if(H[i][mid] == H[j][mid]) {
            ret = mid;
            lo = mid + 1;
        } else
            hi = mid - 1;
    }
    return ret;
}

int query(int l, int r) {
    int ans = M;
    //WTF is this hack
    if(r - l <= RT) {
        for(int i=l;i<=r;i++) {
            ans = bin(R[l], R[i], ans);
        }
    } else {
        int i = l;
        while(i%RT && i <= r) {
            ans = bin(R[i], R[l], ans);
            i++;
        }
        while(i + RT <= r) {
            ans = min(ans, S[i/RT]);
            i += RT;
        }
        while(i <= r) {
            ans = bin(R[i], R[l], ans);
            i++;
        }
    }
    return ans;
}

void update(int pos) {
    S[pos/RT] = M;
    for(int i=(pos/RT) * RT; i < (pos/RT + 1) * RT && i <= N;i++) {
        S[pos/RT] = bin(R[i], R[pos], S[pos/RT]);
    }
}

int readint() {
    int res=0, c;
    while((c = getchar_unlocked()) & 16)
        res = (res << 3) + (res << 1) + (c & 15);
    return res;
}

int main() {
    N = readint();
    M = readint();
    for(int i=1;i<=N;i++) {
        for(int j=0;j<M;j++)
            tmp[j] = getchar_unlocked()&15;
        getchar_unlocked();
        hashify(i);
        R[i] = i;
    }
    for(int i=0;i<RT;i++) S[i] = M;
    for(int i=2;i<=N;i++) {
        if(i/RT == (i - 1) / RT) {
            S[i/RT] = bin(i, i - 1, S[i/RT]);
        }
    }
    //All hashes are computed
    Q = readint();
    for(int i=0, a, b;i<Q;i++) {
        a = readint();
        b = readint();
        printf("%lld\n", 1LL * query(a, b) * (b - a + 1));
        swap(R[a], R[b]);
        if(a/RT != b/RT) {
            update(a);
            update(b);
        }
    }
}
