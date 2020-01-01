#include<bits/stdc++.h>
const int MN=1e5+4, inf=2e9;
struct nd {
    int v,sz,ps,ss,ts,bs,lz;
    bool rev;
    nd *p,*ch[2];
    nd(int i):v(i),sz(1),ps(i),ss(i),ts(i),bs(i),lz(-inf),rev(0),p(0),ch{0}{}
}*lct[MN];
#define gt(a, d) inline int a(nd *n) { return n?n->a:d; }
gt(sz,0)
gt(ps,-inf)
gt(ss,-inf)
gt(ts,0)
gt(bs,-inf)
inline int z(int i) { return std::max(i, 0); }
inline bool par(nd *n) {
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline void psh(nd *n) {
    if(!n) return;
    if(n->lz>-inf) {
        n->v=n->lz;
        n->ts=n->sz*n->lz;
        n->ps=n->ss=n->bs=std::max(n->v,n->ts);
        if(n->ch[0]) n->ch[0]->lz=n->lz;
        if(n->ch[1]) n->ch[1]->lz=n->lz;
        n->lz=-inf;
    }
    if(n->rev) {
        std::swap(n->ps, n->ss);
        std::swap(n->ch[0], n->ch[1]);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
}
inline void upd_sz(nd *n) {
    if(n) n->sz=sz(n->ch[0])+1+sz(n->ch[1]);
}
inline void upd(nd *n) {
    if(!n) return;
    psh(n->ch[0]),psh(n->ch[1]);
    n->ps=std::max(ps(n->ch[0]), ts(n->ch[0])+n->v+z(ps(n->ch[1])));
    n->ss=std::max(ss(n->ch[1]), ts(n->ch[1])+n->v+z(ss(n->ch[0])));
    n->ts=ts(n->ch[0])+n->v+ts(n->ch[1]);
    n->bs=std::max(std::max(bs(n->ch[0]), bs(n->ch[1])), z(ss(n->ch[0]))+n->v+z(ps(n->ch[1])));
}
inline void rot(nd *n, bool b) {
    nd *p=n->p;
    if(p->ch[!b]=n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p) {
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    n->ch[b]=p;
    upd_sz(p);
    psh(p);
    upd(p);
}
inline void splay(nd *n) {
    while(par(n)) {
        bool p = par(n->p);
        if(p) psh(n->p->p);
        psh(n->p),psh(n);
        if(p) {
            bool b = n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b), rot(n,b);
            else rot(n->p,b), rot(n,b);
        } else rot(n, n->p->ch[0]==n);
    }
    upd_sz(n);
    psh(n);
    upd(n);
}
inline nd *access(nd *u) {
    nd *l = 0;
    for(nd *v=u;v;v=v->p) {
        splay(v);
        v->ch[1]=l;
        l=v;
    }
    splay(u);
    return l;
}
inline void evert(nd *u) {
    access(u);
    u->rev^=1;
}
inline nd *path(nd *u, nd *v) {
    evert(u);
    access(v);
    return v;
}
inline void lnk(nd *u,nd *v) {
    evert(u);
    u->p=v;
}
inline void cut(nd *u) {
    access(u);
    if(!u->ch[0]) return;
    u->ch[0]->p=0;
    u->ch[0]=0;
    upd_sz(u);
    upd(u);
}
int N, Q;
int main() {
    scanf("%d",&N);
    for(int i=1,a;i<=N;++i) {
        scanf("%d",&a);
        lct[i] = new nd(a);
    }
    for(int i=1,a,b;i<N;++i) {
        scanf("%d%d",&a,&b);
        lnk(lct[a], lct[b]);
    }
    scanf("%d",&Q);
    for(int i=0,a,b,c,d;i<Q;++i) {
        scanf("%d%d%d",&a,&b,&c);
        if(a == 1) {
            printf("%d\n", z(bs(path(lct[b], lct[c]))));
        } else {
            scanf("%d",&d);
            path(lct[b], lct[c])->lz=d;
        }
    }
}
