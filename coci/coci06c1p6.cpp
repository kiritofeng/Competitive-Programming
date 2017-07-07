#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 304, base = 131, mod = 1000000007;
int R, C;
ll p[MAXN], hsh[2][MAXN][MAXN];
char S[MAXN];

void hasify(int i) {
    hsh[0][i][0] = hsh[1][i][C + 1] = 1;
    for(int j=1;j<=C;++j)
        hsh[0][i][j] = (hsh[0][i][j-1]*base % mod + S[j-1]-'0') % mod;
    for(int j=C;j;--j)
        hsh[1][i][j] = (hsh[1][i][j+1]*base % mod + S[j-1]-'0') % mod;
}

inline ll get_hash(bool type, int i, int l, int r) {
    if(type) return ((hsh[type][i][l] - hsh[type][i][r+1] * p[r - l + 1] % mod) % mod + mod) % mod;
    return ((hsh[type][i][r] - hsh[type][i][l-1] * p[r - l + 1] % mod) % mod + mod) % mod;
}

bool check(int ln) {
    for(int i=1;i<=R-ln+1;++i)
        for(int j=1;j<=C-ln+1;++j) {
            bool b = 1;
            for(int k=0;k<ln;k++)
                if(get_hash(0, i+k, j, j+ln-1)!=get_hash(1, i+ln-k-1, j, j+ln-1))
                    b = 0;
            if(b) return b;
        }
    return 0;
}

int solve() {
    int ans, lo = 0, hi = min(R, C) - 1 >> 1, mid;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        if(check(mid<<1|1))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    ans = hi<<1|1;
    eprintf("Ans: %d\n", ans);
    lo = 0, hi = min(R, C) >> 1;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        if(check(mid<<1))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    ans = max(ans, hi<<1);
    return ans == 1 ? -1 : ans;
}

int main() {
    p[0] = 1;
    for(int i=1;i<MAXN;++i)
        p[i] = p[i-1] * base%mod;
    scanf("%d%d", &R, &C);
    for(int i=1;i<=R;++i) {
        scanf("%s", S);
        hasify(i);
    }
    printf("%d", solve());
}
