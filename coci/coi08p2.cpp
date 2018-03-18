#include<bits/stdc++.h>
const int MN=3e4+4;
int N,Q;
char S[16];
struct nd{
    int val,sum;
    bool rev;
    nd *p,*ch[2];
    nd(int i):val(i),sum(i),rev(0),p(0),ch{0}{}
}*lct[MN];
inline bool par(nd *n){
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline int sum(nd *n){
    return n?n->sum:0;
}
inline void psh(nd *n){
    if(!n) return;
    if(n->rev){
        std::swap(n->ch[0],n->ch[1]);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
}
inline void upd(nd *n){
    if(!n) return;
    n->sum=sum(n->ch[0])+n->val+sum(n->ch[1]);
}
inline void rot(nd *n,bool b){
    nd *tmp=n->p;
    tmp->ch[!b]=n->ch[b];
    if(n->ch[b]) n->ch[b]->p=tmp;
    n->p=tmp->p;
    if(tmp->p){
        if(tmp->p->ch[0]==tmp) n->p->ch[0]=n;
        else if(tmp->p->ch[1]==tmp) n->p->ch[1]=n;
    }
    tmp->p=n;
    n->ch[b]=tmp;
    upd(tmp);
}
inline void splay(nd *n){
    while(par(n)){
        if(par(n->p)) psh(n->p->p);
        psh(n->p);
        psh(n);
        if(par(n->p)){
            bool b=n->p==n->p->p->ch[0];
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        }else rot(n,n->p->ch[0]==n);
    }
    psh(n);
    upd(n);
}
inline nd* access(nd *u){
    nd *tmp=0;
    for(nd *v=u;v;v=v->p){
        splay(v);
        v->ch[0]=tmp;
        tmp=v;
    }
    splay(u);
    return tmp;
}
inline void mkrt(nd *n){
    access(n);
    n->rev^=1;
}
inline bool con(nd *u,nd *v){
    if(u==v) return 1;
    access(u);
    access(v);
    return u->p;
}
inline void lnk(nd *u,nd *v){
    mkrt(u);
    u->p=v;
}
inline int qry(nd *u,nd *v){
    mkrt(u);
    access(v);
    return v->sum;
}
int main(){
    scanf("%d",&N);
    for(int i=1,a;i<=N;++i){
        scanf("%d",&a);
        lct[i]=new nd(a);
    }
    scanf("%d",&Q);
    for(int i=0,a,b;i<Q;++i){
        scanf("%s%d%d",S,&a,&b);
        if(S[0]=='b'){
            if(con(lct[a],lct[b])) puts("no");
            else{
                lnk(lct[a],lct[b]);
                puts("yes");
            }
        }else if(S[0]=='p'){
            splay(lct[a]);
            lct[a]->val=b;
            upd(lct[a]);
        }else if(S[0]=='e'){
            if(!con(lct[a],lct[b])) puts("impossible");
            else printf("%d\n",qry(lct[a],lct[b]));
        }
    }
}
