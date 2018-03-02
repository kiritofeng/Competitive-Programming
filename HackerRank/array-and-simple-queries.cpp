#include<bits/stdc++.h>
struct nd{
    int val,p,sz;
    nd *l,*r;   
    nd(int i):val(i),p(rand()),sz(1),l(0),r(0){}
}*rt;
inline int sz(nd *n){
    return n?n->sz:0;
}
inline void upd(nd *n){
    if(!n) return;
    n->sz=sz(n->l)+1+sz(n->r);
}
void spt(nd *n,nd *&l,nd *&r,int key){
    if(!n)l=r=0;
    else if(sz(n->l)<key)spt(n->r,n->r,r,key-sz(n->l)-1),l=n;
    else spt(n->l,l,n->l,key),r=n;
    upd(n);
}
void mrg(nd *&n,nd *l,nd *r){
    if(!l||!r) n=l?l:r;
    else if(l->p>r->p) mrg(l->r,l->r,r),n=l;
    else mrg(r->l,l,r->l),n=r;
    upd(n);
}
int lft(nd *n){
    if(!n->l) return n->val;
    else return lft(n->l);
}
int rht(nd *n){
    if(!n->r) return n->val;
    else return rht(n->r);
}
void dfs(nd *n){
    if(!n) return;
    dfs(n->l);
    printf("%d ",n->val);
    dfs(n->r);
}
int N,M;
int main(){
    scanf("%d%d",&N,&M);
    for(int i=0,a;i<N;++i){
        scanf("%d",&a);
        mrg(rt,rt,new nd(a));
    }
    for(int i=0,a,b,c;i<M;++i){
        scanf("%d%d%d",&a,&b,&c);
        nd *l=0,*m=0,*r=0;
        spt(rt,m,r,c);
        spt(m,l,m,b-1);
        if(a==1){
            mrg(m,m,l); 
            mrg(rt,m,r);
        }else{
            mrg(m,r,m);
            mrg(rt,l,m);
        }
    }
    printf("%d\n",abs(rht(rt)-lft(rt)));
    dfs(rt);
}
