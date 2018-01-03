#include<bits/stdc++.h>
typedef long long ll;
const ll LINF=0x3f3f3f3f3f3f3f3f;
template<typename T>
inline T max(T t){
    return t;
}
template<typename T,typename ...Args>
inline T max(T t, Args... args){
    return t>max(args...)?t:max(args...);
}
int N,M;
struct nd{
    int val,p,sz,lz;
    nd *l,*r;
    ll psum,ssum,tsum,bsum;
    bool rev,lzit;
    nd(int i):val(i),p(rand()),sz(1),lz(0),psum(i),ssum(i),tsum(i),bsum(i),rev(0),lzit(0),l(0),r(0){}
}*rt;
char S[16];
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
inline void psh(nd *n){
    if(!n) return;
    // set value
    if(n->lzit){
        n->val=n->lz;
        n->psum=n->ssum=n->bsum=1LL*(n->lz<=0?1:n->sz)*(n->lz);
        n->tsum=1LL*(n->sz)*(n->lz);
        if(n->l){
            n->l->lz=n->lz;
            n->l->lzit=1;
        }
        if(n->r){
            n->r->lz=n->lz;
            n->r->lzit=1;
        }
        n->lzit=0;
    }
    if(n->rev){
        std::swap(n->l,n->r);
        std::swap(n->psum,n->ssum);
        if(n->l)
            n->l->rev^=1;
        if(n->r)
            n->r->rev^=1;
        n->rev=0;
    }
}
inline ll zero(ll l){
    return std::max(l,0LL);
}
inline void upd(nd *n){
    if(!n) return;
    ll lbsum=n->val;
    n->bsum=n->val;
    n->tsum=n->val;
    psh(n->l);
    psh(n->r);
    if(n->l){
        n->psum=max(psum(n->l),tsum(n->l)+n->val+zero(psum(n->r)));
        n->bsum=max(n->bsum,bsum(n->l),ssum(n->l)+n->val);
        n->tsum+=tsum(n->l);
        lbsum+=ssum(n->l);
    }else{
        n->psum=n->val+zero(psum(n->r));
    }
    if(n->r){
        n->ssum=max(ssum(n->r),tsum(n->r)+n->val+zero(ssum(n->l)));
        n->bsum=max(n->bsum,bsum(n->r),lbsum+psum(n->r),n->val+psum(n->r));
        n->tsum+=tsum(n->r);
    }else{
        n->ssum=n->val+zero(ssum(n->l));
    }
    n->sz=sz(n->l)+1+sz(n->r);
}
void mrg(nd *&n,nd *l,nd *r){
    psh(l),psh(r);
    if(!l||!r) n=l?l:r;
    else if(l->p>r->p) mrg(l->r,l->r,r),n=l;
    else mrg(r->l,l,r->l),n=r;
    upd(n);
}
void spt(nd *n,nd *&l,nd *&r,int key){
    psh(n);
    if(!n) l=r=0;
    else if(sz(n->l)<key) spt(n->r,n->r,r,key-sz(n->l)-1),l=n;
    else spt(n->l,l,n->l,key),r=n;
    upd(n);
}
int main() {
    srand(0);
    scanf("%d%d",&N,&M);
    for(int i=0,a;i<N;++i){
        scanf("%d",&a);
        mrg(rt,rt,new nd(a));
    }
    for(int i=0,a,b,c;i<M;++i){
        scanf("%s",S);
        if(!strcmp(S,"INSERT")){
            scanf("%d%d",&a,&b);
            nd *tmp=0,*l=0,*m=0,*r=0;
            for(int j=0,d;j<b;++j){
                scanf("%d",&d);
                mrg(tmp,tmp,new nd(d));
            }
            spt(rt,l,r,a);
            mrg(m,l,tmp);
            mrg(rt,m,r);
        }else if(!strcmp(S,"DELETE")){
            scanf("%d%d",&a,&b);
            nd *tmp=0,*l=0,*m=0,*r=0;
            spt(rt,l,tmp,a-1);
            spt(tmp,m,r,b);
            mrg(rt,l,r);
        }else if(!strcmp(S,"MAKE-SAME")){
            scanf("%d%d%d",&a,&b,&c);
            nd *tmp=0,*l=0,*m=0,*r=0;
            spt(rt,l,tmp,a-1);
            spt(tmp,m,r,b);
            if(m) m->lz=c,m->lzit=1;
            mrg(tmp,m,r);
            mrg(rt,l,tmp);
        }else if(!strcmp(S,"REVERSE")){
            scanf("%d%d",&a,&b);
            nd *tmp=0,*l=0,*m=0,*r=0;
            spt(rt,l,tmp,a-1);
            spt(tmp,m,r,b);
            if(m) m->rev^=1;
            mrg(tmp,m,r);
            mrg(rt,l,tmp);
        }else if(!strcmp(S,"GET-SUM")){
            scanf("%d%d",&a,&b);
            nd *tmp=0,*l=0,*m=0,*r=0;
            spt(rt,l,tmp,a-1);
            spt(tmp,m,r,b);
            printf("%lld\n",tsum(m));
            mrg(tmp,m,r);
            mrg(rt,l,tmp);
        }else{
            printf("%lld\n",bsum(rt));
        }
    }
}
