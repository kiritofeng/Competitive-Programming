#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXLEN = 1000004, seed = 257, mod = 1000000007;
int K, len, ans;
char S[MAXLEN];
ll e[MAXLEN], h[MAXLEN];

ll hsh(int i, int l) {
    //This is pure insanity
    return ((h[i + l] - e[l] * h[i]) % mod + mod) % mod;
}

int bin(int i, int j) {
    int lo = 0, hi = K, mid;
    while(lo <= hi) {
        mid = lo + hi >> 1;
        if(hsh(i, mid)!=hsh(j, mid))
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return lo;
}

int main() {
    scanf("%s\n%d", &S, &K);
    len = strlen(S);
    h[0] = S[0] % mod;
    e[0] = 1;
    for(int i=1;i<len;i++) {
        h[i] = (h[i - 1] * seed % mod + S[i]) % mod;
        e[i] = (e[i - 1] * seed) % mod;
    }
    for(int i=1, j;i<=len-K;i++) {
        if(S[i] != S[ans]) {
            //Have to handle this seperately...
            if(S[i] < S[ans])
                ans = i;
            continue;
        } else {
            j = bin(ans, i);
            //j is the first character that is not equal
            if(S[i + j] < S[ans + j]) ans = i;
        }
    }
    for(int i=0;i<K;i++)
        putchar(S[ans + i]);
}
