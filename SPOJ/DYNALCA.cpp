#include<bits/stdc++.h>
const int MN=1e5+4;
int N,M;
char S[8];
struct nd{
    int val;
    nd *p,*ch[2];
    nd(int i):val(i),p(0),ch{0}{}
}*lct[MN];
inline bool par(nd *n){
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline void rot(nd *n,bool b){
    nd *p=n->p;
    p->ch[!b]=n->ch[b];
    if(n->ch[b]) n->ch[b]->p=p;
    n->p=p->p;
    if(p->p){
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        else if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    n->ch[b]=p;
}
inline void splay(nd *n){
    while(par(n)){
        if(par(n->p)){
            bool b=n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        }else rot(n,n->p->ch[0]==n);
    }
}
inline nd* access(nd *u){
    nd *lst=0;
    for(nd *v=u;v;v=v->p){
        splay(v);
        v->ch[1]=lst;
        lst=v;
    }
    splay(u);
    return lst;
}
inline nd* lca(nd *u,nd *v){
    access(u);
    return access(v);
}
inline void lnk(nd *u,nd *v){
    access(u);
    u->p=v;
}
inline void cut(nd *u){
    access(u);
    u->ch[0]->p=0;
    u->ch[0]=0;
}
int main(){
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;++i) lct[i]=new nd(i);
    for(int i=0,a,b;i<M;++i){
        scanf("%s",S);
        if(S[0]=='c'){
            scanf("%d",&a);
            cut(lct[a]);
        }else{
            scanf("%d%d",&a,&b);
            if(S[1]=='c'){
                printf("%d\n",lca(lct[a],lct[b])->val);
            }else{
                lnk(lct[a],lct[b]);
            }
        }
    }
}
