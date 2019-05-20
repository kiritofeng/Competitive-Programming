#include<bits/stdc++.h>
const int inf=0x3f3f3f3f;
struct nd{
    int v,sz,lz,ps,ss,ts,bs;
    bool rev;
    nd *p,*ch[2];
    nd(int i):v(i),sz(1),lz(-inf),ps(i),ss(i),ts(i),bs(i),rev(0),p(0),ch{0}{};
}*rt;
#define gt(a,d) inline int a(nd *n){return n?n->a:d;}
gt(sz,0)
gt(ps,-inf)
gt(ss,-inf)
gt(ts,0)
gt(bs,-inf)
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
        std::swap(n->ch[0],n->ch[1]);
        std::swap(n->ps,n->ss);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
}
inline int z(int i){return std::max(i,0);}
inline void upd(nd *n) {
    if(!n) return;
    psh(n->ch[0]), psh(n->ch[1]);
    n->sz=sz(n->ch[0])+1+sz(n->ch[1]);
    n->ts=ts(n->ch[0])+n->v+ts(n->ch[1]);
    n->ps=std::max(ps(n->ch[0]),ts(n->ch[0])+n->v+z(ps(n->ch[1])));
    n->ss=std::max(ss(n->ch[1]),ts(n->ch[1])+n->v+z(ss(n->ch[0])));
    n->bs=std::max(std::max(bs(n->ch[0]),bs(n->ch[1])),z(ss(n->ch[0]))+n->v+z(ps(n->ch[1])));
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
    psh(p);
    upd(p);
}
inline nd *splay(nd *n,nd *r=0) {
    while(n->p!=r) {
        bool p=n->p->p!=r;
        if(p) psh(n->p->p);
        psh(n->p),psh(n);
        if(p) {
            bool b=n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        }else rot(n,n->p->ch[0]==n);
    }
    psh(n);
    upd(n);
    return n;
}
inline void ins(int i,int p) {
    if(!rt) {
        rt=new nd(i);
        return;
    }
    nd *n=rt;
    while(n) {
        psh(n);
        bool b=sz(n->ch[0])<p;
        if(!n->ch[b]) {
            n->ch[b]=new nd(i);
            n->ch[b]->p=n;
            n=n->ch[b];
            break;
        }
        p-=b*(sz(n->ch[0])+1);
        n=n->ch[b];
    }
    splay(rt=n);
}
inline nd *fnd(int p,nd *r=0) {
    nd *n=rt;
    while(n) {
        psh(n);
        if(sz(n->ch[0])+1==p) {
            return splay(n,r);
        }
        bool b=sz(n->ch[0])+1<=p;
        p-=b*(sz(n->ch[0])+1);
        n=n->ch[b];
    }
    return 0;
}
inline void rng(int a,int b) {
    rt=fnd(a);
    fnd(a+b+1,rt);
}
int N,M;
char S[16];
#define is(X) !strcmp(X,S)
int main() {
    scanf("%d%d",&N,&M);
    ins(-inf,1);
    ins(-inf,1);
    for(int i=1,a;i<=N;++i) {
        scanf("%d",&a);
        ins(a,i);
    }
    for(int i=0,a,b,c;i<M;++i) {
        scanf("%s",S);
        if(is("INSERT")) {
            scanf("%d%d",&a,&b);
            for(int j=1;j<=b;++j) {
                scanf("%d",&c);
                ins(c,a+j);
            }
        }else if(is("DELETE")) {
            scanf("%d%d",&a,&b);
            rng(a,b);
            rt->ch[1]->ch[0]=0;
            upd(rt->ch[1]), upd(rt);
        }else if(is("MAKE-SAME")) {
            scanf("%d%d%d",&a,&b,&c);
            rng(a,b);
            rt->ch[1]->ch[0]->lz=c;
            rt=splay(rt->ch[1]->ch[0]);
        }else if(is("REVERSE")) {
            scanf("%d%d",&a,&b);
            rng(a,b);
            rt->ch[1]->ch[0]->rev^=1;
            rt=splay(rt->ch[1]->ch[0]);
        }else if(is("GET-SUM")) {
            scanf("%d%d",&a,&b);
            rng(a,b);
            printf("%d\n",ts(rt->ch[1]->ch[0]));
        }else if(is("MAX-SUM")) {
            printf("%d\n",bs(rt));
        }
    }
}
