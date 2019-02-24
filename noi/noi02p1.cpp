#include<bits/stdc++.h>
const int MN=30004;
int T;
char c;
struct nd{
    int sz;
    nd *p,*ch[2];
    nd():sz(1),p(0),ch{0}{};
}*shit[MN];
inline int sz(nd *n) {
    return n?n->sz:0;
}
inline void upd(nd *n) {
    n->sz=sz(n->ch[0])+1+sz(n->ch[1]);
}
inline void rot(nd *n,bool b) {
    nd *p=n->p;
    if(p->ch[!b]=n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p) {
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    upd(n->ch[b]=p);
}
inline void splay(nd *n) {
    while(n->p) {
        if(n->p->p) {
            bool b=n->p->p->ch[0]==n->p;
            if(n->p->ch[b] == n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        } else rot(n, n->p->ch[0]==n);
    }
    upd(n);
}
inline void mrg(nd *u,nd *v) {
    splay(v);
    while(v->ch[1]) v = v->ch[1];
    splay(u);
    while(u->ch[0]) u = u->ch[0];
    splay(u);
    v->ch[1] = u;
    u->p=v;
    splay(u);
}
inline bool con(nd *u,nd *v) {
    splay(u);
    splay(v);
    return u->p;
}
inline int qry(nd *u,nd *v) {
    if(!con(u,v)) return -1;
    splay(u);
    int ret = sz(u->ch[0]);
    splay(v);
    ret -= sz(v->ch[0]);
    return std::max(abs(ret)-1,0);
}
int main() {
    assert(scanf("%d",&T)==1);
    for(int i=0;i<MN;++i)
        shit[i] = new nd();
    for(int i=0,a,b;i<T;++i) {
        assert(scanf(" %c%d%d",&c,&a,&b)==3);
        if(c=='M') {
            mrg(shit[a],shit[b]);
        } else {
            printf("%d\n",qry(shit[a],shit[b]));
        }
    }
}
