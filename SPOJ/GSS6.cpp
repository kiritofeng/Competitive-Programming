#include<bits/stdc++.h>
#define INIT nd *l=0,*m=0,*r=0,*tmp=0;
#define SPLIT spt(rt,l,tmp,a-1),spt(tmp,m,r,1);
#define MERGE mrg(tmp,m,r),mrg(rt,l,tmp);
typedef long long ll;
const ll LINF=0x3f3f3f3f3f3f3f3f;
struct nd{
    int val,p,sz;
    ll psum,ssum,tsum,bsum;
    nd *l,*r;
    nd(int i):val(i),p(rand()),sz(1),psum(i),ssum(i),tsum(i),bsum(i),l(0),r(0){}
}*rt;
template<typename T>
inline T max(T t){
    return t;
}
template<typename T,typename... A>
inline T max(T t,A... a){
    T res=max(a...);
    return res>t?res:t;
}
inline int sz(nd *n){
    return n?n->sz:0;
}
inline ll psum(nd *n){
    return n?n->psum:0;
}
inline ll ssum(nd *n){
    return n?n->ssum:0;
}
inline ll tsum(nd *n){
    return n?n->tsum:0;
}
inline ll bsum(nd *n){
    return n?n->bsum:-LINF;
}
inline ll zero(ll l){
    return max(l,0);
}
inline void upd(nd *n){
    if(!n) return;
    n->sz=1;
    n->bsum=n->tsum=n->val;
    if(n->l){
        n->psum=max(n->l->psum,n->l->tsum+n->val+zero(psum(n->r)));
        n->sz+=n->l->sz;
        n->tsum+=n->l->tsum;
        n->bsum=max(n->bsum,n->l->bsum,n->l->ssum+n->val);
    }else
        n->psum=n->val+zero(psum(n->r));
    if(n->r){
        n->ssum=max(n->r->ssum,n->r->tsum+n->val+zero(ssum(n->l)));
        n->sz+=n->r->sz;
        n->tsum+=n->r->tsum;
        n->bsum=max(n->bsum,n->r->bsum,n->r->psum+n->val+zero(ssum(n->l)));
    }else
        n->ssum=n->val+zero(ssum(n->l));
}
void spt(nd *n,nd *&l,nd *&r,int key){
    if(!n) l=r=0;
    else if(sz(n->l)<key) spt(n->r,n->r,r,key-sz(n->l)-1),l=n;
    else spt(n->l,l,n->l,key),r=n;
    upd(n);
}
void mrg(nd *&n,nd *l,nd *r){
    if(!l||!r) n=l?l:r;
    else if(l->p>r->p) mrg(l->r,l->r,r),n=l;
    else mrg(r->l,l,r->l),n=r;
    upd(n);
}
int N,Q;
char c;
int main(){
    scanf("%d",&N);
    for(int i=0,a;i<N;++i){
        scanf("%d",&a);
        mrg(rt,rt,new nd(a));
    }
    scanf("%d",&Q);
    for(int i=0,a,b;i<Q;++i){
        scanf(" %c",&c);
        if(c=='I'){
            scanf("%d%d",&a,&b);
            INIT
            SPLIT
            mrg(m,new nd(b),m);
            MERGE
        }else if(c=='D'){
            scanf("%d",&a);
            INIT
            SPLIT
            mrg(rt,l,r);
        }else if(c=='R'){
            scanf("%d%d",&a,&b);
            INIT
            SPLIT
            m=new nd(b);
            MERGE
        }else{
            scanf("%d%d",&a,&b);
            INIT
            spt(rt,tmp,r,b),spt(tmp,l,m,a-1);
            printf("%lld\n",bsum(m));
            mrg(tmp,l,m),mrg(rt,tmp,r);
        }
    }
}
