#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int IT = 10, MAXN = 1000004, seed = 131, mod = 1000000009;
ll h[2][MAXN], p[MAXN] = {1};
char S[MAXN];

inline ll gethash1(int l, int r) {
    return ((h[0][r] - h[0][l - 1] * p[r - l + 1] % mod) % mod + mod) % mod;
}

inline ll gethash2(int l, int r) {
    return ((h[1][l] - h[1][r + 1] * p[r - l + 1] % mod) % mod + mod) % mod;
}

inline ll gethash(int l, int r, bool type) {
    if(type) return gethash2(l, r);
    return gethash1(l, r);
}

int main() {
    for(int i=1;i<MAXN;i++) p[i] = p[i - 1] * seed % mod;
    for(int i=0, j, k, len;i<IT;i++) {
        scanf("%s", S);
        len = strlen(S);
        memset(h, 0, sizeof h);
        for(j=1;j<=len;j++)
            h[0][j] = (h[0][j - 1] * seed % mod + S[j - 1]) % mod;
        for(j=len;j;j--)
            h[1][j] = (h[1][j + 1] * seed % mod + S[j - 1]) % mod;
        for(j=1, k = 0;(j << 1) <= len;j++) {
            //Odd Case
            if(gethash(1, j, 0) == gethash(j, (j << 1) - 1, 1) || gethash(len - j + 1, len, 0) == gethash(len - (j - 1 << 1), len - j + 1, 1)) k = (j << 1) - 1;
            //Even Case
            if(gethash(1, j, 0) == gethash(j + 1, j << 1, 1) || gethash(len - j + 1, len, 0) == gethash(len - (j << 1) + 1, len - j, 1)) k = j << 1;
        }
        printf("%d\n", len - k);
    }
}
