#include <bits/stdc++.h>
#include "momoka.h"
typedef long long ll;
const int ML=1e6+4, MA=26;
int n,sz,lst,c[ML],len[ML],cnt[ML],suf[ML][MA],to[ML][MA];
int scnt,state[ML];
ll ans;
void Init() {
    len[1] = -1;
    for(int i=0;i<MA;++i)
        suf[0][i] = 1;
    c[n++] = -1;
    sz = 2;
}
ll Type(char letter) {
    c[n++] = letter - 'a';
    state[scnt++] = lst;
    if(c[n - 1] != c[n - len[lst] - 2])
        lst = suf[lst][c[n - 1]];
    if(!to[lst][c[n - 1]]) {
        int u = to[suf[lst][c[n - 1]]][c[n - 1]];
        for(int i = 0; i < MA; ++i)
            suf[sz][i] = suf[u][i];
        suf[sz][c[n - len[u] - 1]] = u;
        len[sz] = len[lst] + 2;
        cnt[sz] = cnt[u] + 1;
        to[lst][c[n - 1]] = sz++;
    }
    lst = to[lst][c[n - 1]];
    return ans += cnt[lst];
}
void Backspace() {
    --n;
    ans -= cnt[lst];
    lst = state[--scnt];
}
