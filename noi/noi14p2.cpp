#include<bits/stdc++.h>
const int inf=0x3f3f3f3f,MN=5e4+4,MM=1e5+4;
int N,M,ans=inf;
struct edge{
    int u,v,a,b;
}E[MM];
struct nd{
    int id,val,mx,mid;
    bool rev;
    nd *p,*ch[2];
    nd(int i,int v):id(i),val(v),mx(v),mid(i),rev(0),p(0),ch{0}{}
}*lct[MN+MM];
inline bool par(nd *n) {
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline void psh(nd *n) {
    if(n->rev) {
        std::swap(n->ch[0],n->ch[1]);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
}
inline int mx(nd *n) {
    return n?n->mx:-inf;
}
inline void upd(nd *n) {
    n->mx=std::max(std::max(mx(n->ch[0]),mx(n->ch[1])),n->val);
    if(n->mx==mx(n->ch[0])) n->mid=n->ch[0]->mid;
    else if(n->mx==mx(n->ch[1])) n->mid=n->ch[1]->mid;
    else n->mid=n->id;
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
    while(par(n)) {
        bool p=par(n->p);
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
}
inline nd *access(nd *u) {
    nd *l=0;
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
inline bool con(nd *u,nd *v) {
    if(u==v) return 1;
    access(u);
    access(v);
    return u->p;
}
inline void lnk(nd *u,nd *v) {
    evert(u);
    u->p=v;
}
inline void cut(nd *u,nd *v) {
    evert(u);
    access(v);
    if(!v->ch[0]) return;
    v->ch[0]->p=0;
    v->ch[0]=0;
    upd(v);
}
inline int qry(nd *u,nd *v) {
    evert(u);
    access(v);
    return v->mid;
}
int main() {
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;++i) {
        scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].a,&E[i].b);
    }
    std::sort(E+1,E+M+1,[](const edge &E1, const edge &E2){
        return E1.a < E2.a;
    });
    // 1 -> N are nodes, N -> N + M are edges
    for(int i=1;i<=N;++i) lct[i]=new nd(i,0);
    for(int i=1;i<=M;++i) {
        // WTF NOI...
        if(E[i].u==E[i].v) continue;
        if(con(lct[E[i].u],lct[E[i].v])) {
            int id=qry(lct[E[i].u],lct[E[i].v])-N;
            if(E[id].b<=E[i].b) continue;
            cut(lct[N+id],lct[E[id].u]);
            cut(lct[N+id],lct[E[id].v]);
        }
        lct[N+i]=new nd(N+i,E[i].b);
        lnk(lct[N+i],lct[E[i].u]);
        lnk(lct[N+i],lct[E[i].v]);
        if(con(lct[1],lct[N])) {
            ans=std::min(ans,E[qry(lct[1],lct[N])-N].b+E[i].a);
        }
    }
    printf("%d\n",ans==inf?-1:ans);
}
