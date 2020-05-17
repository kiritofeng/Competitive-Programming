#include<bits/stdc++.h>
typedef long long ll;
const int ML=3e5+4,MA=26;
int sz,lst,n,len[ML],c[ML],lnk[ML],lz[ML],to[ML][MA];
ll ans;
char S[ML];
inline void init() {
    len[1] = -1;
    lnk[0] = 1;
    c[n++] = -1;
    sz = 2;
}
inline int suf(int u) {
    while(c[n - len[u] - 2] != c[n - 1])
        u = lnk[u];
    return u;
}
inline void ins(int i) {
    c[n++] = i - 'a';
    lst = suf(lst);
    if(!to[lst][i - 'a']) {
        len[sz] = len[lst] + 2;
        lnk[sz] = to[suf(lnk[lst])][i - 'a'];
        to[lst][i - 'a'] = sz++;
    }
    lst = to[lst][i - 'a'];
    lz[lst] += 1;
}
int main() {
    scanf("%s",S);
    init();
    for(int i=0;S[i];++i)
        ins(S[i]);
    for(int i=sz-1;i;--i) {
        lz[lnk[i]] += lz[i];
        ans = std::max(ans, 1LL * len[i] * lz[i]);
    }
    printf("%lld\n", ans);
}
