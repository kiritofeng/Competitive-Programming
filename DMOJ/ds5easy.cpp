#include<bits/stdc++.h>
const int MN=1e5+4,inf=2e9;
struct nd{
    int id,val,sz,sum,mn,mx,st,inc;
    bool rev,lz;
    nd *p,*ch[2];
    nd(int i,int v):id(i),val(v),sz(1),sum(v),mn(v),mx(v),st(0),inc(0),rev(0),lz(0),p(0),ch{0}{};
}*lct[MN];
inline bool par(nd *n){
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
#define gt(p,d) inline int p(nd *n) { return n?n->p:d; }
gt(sz,0)
gt(mn,INT_MAX)
gt(mx,INT_MIN)
gt(sum,0)
inline void psh(nd *n){
    if(!n) return;
    if(n->rev) {
        std::swap(n->ch[0],n->ch[1]);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
    if(n->lz) {
        n->val=n->mn=n->mx=n->st;
        n->sum=n->st*n->sz;
        if(n->ch[0]){
            n->ch[0]->st=n->st;
            n->ch[0]->inc=0;
            n->ch[0]->lz=1;
        }
        if(n->ch[1]){
            n->ch[1]->st=n->st;
            n->ch[1]->inc=0;
            n->ch[1]->lz=1;
        }
        n->lz=0;
    }
    if(n->inc) {
        n->val+=n->inc;
        n->mn+=n->inc;
        n->mx+=n->inc;
        n->sum+=n->inc*n->sz;
        if(n->ch[0]) n->ch[0]->inc+=n->inc;
        if(n->ch[1]) n->ch[1]->inc+=n->inc;
        n->inc=0;
    }
}
inline void upd_sz(nd *n) {
    if(n) n->sz=sz(n->ch[0]) + 1 + sz(n->ch[1]);
}
inline void upd(nd *n) {
    if(!n) return;
    psh(n->ch[0]), psh(n->ch[1]);
    n->mx=std::max(std::max(mx(n->ch[0]), mx(n->ch[1])), n->val);
    n->mn=std::min(std::min(mn(n->ch[0]), mn(n->ch[1])), n->val);
    n->sum=sum(n->ch[0]) + n->val + sum(n->ch[1]);
}
inline void rot(nd *n,bool b) {
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
inline void splay(nd *n){
    while(par(n)) {
        bool p = par(n->p);
        if(p) psh(n->p->p);
        psh(n->p), psh(n);
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
inline nd *lca(nd *u,nd *v) {
    access(u);
    return access(v);
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
int N,M,R;
int main() {
    scanf("%d%d",&N,&M);
    for(int i=1,a;i<=N;++i) {
        scanf("%d",&a);
        lct[i] = new nd(i,a);
    }
    for(int i=1,a,b;i<N;++i) {
        scanf("%d%d",&a,&b);
        lnk(lct[a],lct[b]);
    }
    scanf("%d",&R);
    evert(lct[R]);
    for(int i=0,a,b,c,d;i<M;++i){
        scanf("%d",&a);
        if(a==0) {
            scanf("%d",&b);
            R=b;
            evert(lct[R]);
        }else if(a==1) {
            scanf("%d%d%d",&b,&c,&d);
            nd *p=path(lct[b],lct[c]);
            p->st=d;
            p->lz=1;
            evert(lct[R]);
        }else if(a==2) {
            scanf("%d%d%d",&b,&c,&d);
            nd *p=path(lct[b],lct[c]);
            p->inc+=d;
            evert(lct[R]);
        }else if(a==3) {
            scanf("%d%d",&b,&c);
            nd *p=path(lct[b],lct[c]);
            printf("%d\n",p->mn);
            evert(lct[R]);
        }else if(a==4) {
            scanf("%d%d",&b,&c);
            nd *p=path(lct[b],lct[c]);
            printf("%d\n",p->mx);
            evert(lct[R]);
        }else if(a==5) {
            scanf("%d%d",&b,&c);
            nd *p=path(lct[b],lct[c]);
            printf("%d\n",p->sum);
            evert(lct[R]);
        }else if(a==6) {
            scanf("%d%d",&b,&c);
            nd *l = lca(lct[b],lct[c]);
            if(l == lct[b]) continue;
            cut(lct[b]);
            lnk(lct[b],lct[c]);
            evert(lct[R]);
        }else if(a==7) {
            scanf("%d%d",&b,&c);
            nd *l = lca(lct[b],lct[c]);
            printf("%d\n",l->id);
        }
    }
}
