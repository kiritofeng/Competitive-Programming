#include<bits/stdc++.h>
const int MN=30004;
int T, par[MN], inc[MN], sz[MN];
char c;
inline int rt(int a) {
    while(~par[a]) a = par[a];
    return a;
}
inline int qry(int a) {
    int ret = 0;
    while(~a) {
        ret += inc[a];
        a = par[a];
    }
    return ret;
}
inline int qry(int a,int b) {
    if(rt(a) != rt(b)) return -1;
    return abs(qry(a)-qry(b)) - 1;
}
inline void mrg(int a,int b) {
    a = rt(a); b = rt(b);
    if(sz[a] <= sz[b]) {
        par[a] = b;
        inc[a] += sz[b] - inc[b];
        sz[b] += sz[a];
    } else {
        par[b] = a;
        inc[a] += sz[b];
        inc[b] -= inc[a];
        sz[a] += sz[b];
    }
}
int main() {
    memset(par, -1, sizeof par);
    for(int i=1;i<MN;++i) sz[i] = 1;
    scanf("%d",&T);
    for(int i=0,a,b;i<T;++i) {
        scanf(" %c%d%d",&c,&a,&b);
        if(c=='M') {
            mrg(a,b);
        } else {
            printf("%d\n",qry(a,b));
        }
    }
}
