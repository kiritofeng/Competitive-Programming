#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
const int MN=15e4+4,MM=15e4+4;
struct nd{
    int val,sum;
    nd *p,*ch[2];
    nd():val(0),sum(0),p(0),ch{0}{}
};
std::map<int,nd*>lct;
std::map<int,int>cnt;
int N,L,*X;
inline bool par(nd *n){
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline int sum(nd *n){
    return n?n->sum:0;
}
inline void upd(nd *n){
    n->sum=sum(n->ch[0])+n->val+sum(n->ch[1]);
}
inline void rot(nd *n,bool b){
    nd *p=n->p;
    p->ch[!b]=n->ch[b];
    if(n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p){
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        else if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    upd(n->ch[b]=p);
}
inline void splay(nd *n){
    while(par(n)){
        if(par(n->p)){
            bool b=n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        }else rot(n,n->p->ch[0]==n);
    }
    upd(n);
}
inline nd *access(nd *u){
    nd *lst=0;
    for(nd *v=u;v;v=v->p){
        splay(v);
        v->ch[1]=lst;
        lst=v;
    }
    splay(u);
    return lst;
}
inline void lnk(nd *u,nd *v){
    access(u);
    u->p=v;
}
inline void cut(nd *u){
    access(u);
    if(!u->ch[0]) return;
    u->ch[0]->p=0;
    u->ch[0]=0;
}
inline int qry(nd *u){
    access(u);
    return sum(u);
}
inline void mod(nd *n,int i){
    splay(n);
    n->val=i;
    upd(n);
}
inline void crt(int i){
    if(lct.count(i)) return;
    lct[i]=new nd();
    lnk(lct[i],lct.lower_bound(i+1)->second);
    if(lct.begin()->first==i) return;
    auto lst=std::prev(lct.lower_bound(i));
    if(cnt[lst->first]) return;
    cut(lst->second);
    lnk(lst->second,lct[i]);
}
inline void add(int i){
    crt(i+L+1);
    crt(i);
    if(!cnt[i]++){
        cut(lct[i]);
        lnk(lct[i],lct[i+L+1]);
        mod(lct[i],1);
    }
}
inline void rem(int i){
    if(!--cnt[i]){
        cut(lct[i]);
        lnk(lct[i],lct.lower_bound(i+1)->second);
        mod(lct[i],0);
    }
}
void init(int _N,int _L,int* _X){
    N=_N;
    L=_L;
    X=_X;
    lct[0]=new nd();
    lct[2e9]=new nd();
    for(int i=0;i<N;++i)
        add(X[i]);
}
int update(int i,int y){
    rem(X[i]);
    add(y);
    X[i]=y;
    return qry(lct[0]);
}
#ifndef SIGNATURE_GRADER
int _N,_M,_L,_X[MN],_I[MM],_Y[MN];
int main(){
    scanf("%d%d%d",&_N,&_L,&_M);
    for(int i=0;i<_N;++i)
        scanf("%d",_X+i);
    init(_N,_L,_X);
    for(int i=0,a,b;i<_M;++i){
        scanf("%d%d",_I+i,_Y+i);
        printf("%d\n",update(_I[i],_Y[i]));
    }
}
#endif
