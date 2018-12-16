#include<bits/stdc++.h>
typedef std::pair<int, int> pii;
const int MN=1e5+4;
int N, M , Q, low[MN], hi[MN], D[MN], delta[MN];
std::vector<pii> adj[MN];
struct nd {
    int id;
    nd *p,*ch[2];
    nd(int i):id(i),p(0),ch{0}{};
}*lct[MN];
inline bool par(nd *n) {
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline void rot(nd *n, bool b) {
    nd *p=n->p;
    if(p->ch[!b]=n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p) {
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        else if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    n->ch[b]=p;
}
inline void splay(nd *n) {
    while(par(n)) {
        if(par(n->p)) {
            bool b = n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        } else rot(n,n->p->ch[0]==n);
    }
}
inline nd *access(nd *u) {
    nd *lst=0;
    for(nd *v=u;v;v=v->p) {
        splay(v);
        v->ch[1]=lst;
        lst=v;
    }
    splay(u);
    return lst;
}
inline nd *rt(nd *u) {
    access(u);
    nd *ret=u;
    while(ret->ch[0]) ret=ret->ch[0];
    splay(ret);
    return ret;
}
inline void lnk(nd *u,nd *v) {
    access(u);
    u->p=v;
}
inline void cut(nd *u) {
    access(u);
    if(u->ch[0]) u->ch[0]->p=0;
    u->ch[0]=0;
}
inline bool con(nd *u, nd *v) {
    if(u == v) return 1;
    access(u);
    access(v);
    return u->p;
}
void dfs(int src, int p) {
    D[src] = 1;
    for(pii e : adj[src]) {
        if(e.first == p) continue;
        low[e.second] = e.first;
        hi[e.second] = src;
        dfs(e.first, src);
    }
}
int main() {
    scanf("%d%d%d", &N, &M, &Q);
    for(int i = 1; i <=N; ++i)
        lct[i] = new nd(i);
    for(int i = 1, a, b; i < N; ++i) {
        scanf("%d%d", &a, &b);
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
    dfs(1, -1);
    for(int i = 0, a; i < M; ++i) {
        scanf("%d", &a);
        int r = rt(lct[hi[a]])->id;
        if(con(lct[low[a]], lct[hi[a]])) {
            D[low[a]] = D[r];
            cut(lct[low[a]]);
            delta[low[a]] = D[low[a]];
        } else {
            D[r] += D[low[a]] - delta[low[a]];
            lnk(lct[low[a]], lct[hi[a]]);
        }
    }
    for(int i = 0, a; i < Q; ++i) {
        scanf("%d", &a);
        printf("%d\n", D[rt(lct[a])->id]);
    }
}
