#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef std::pair<int,int>pii;
const int MN=1e5+4;
struct nd{
    int val,p,sz;
    ll sum;
    nd *l,*r;   
    nd(int i):val(i),sum(i),sz(1),p(rand()),l(0),r(0){}
};
int K,N;
ll ans,base;
struct person{
    int b1,b2;
    char z1,z2;
}P[MN];
inline int sz(nd *n){
    return n?n->sz:0;
}
inline ll sum(nd *n){
    return n?n->sum:0LL;
}
inline void upd(nd *n){
    if(!n) return;
    n->sz=sz(n->l)+1+sz(n->r);
    n->sum=sum(n->l)+n->val+sum(n->r);
}
void spt(nd *n,nd *&l,nd *&r,int key){
    if(!n) l=r=0;
    else if(n->val<=key) spt(n->r,n->r,r,key),l=n;
    else spt(n->l,l,n->l,key),r=n;
    upd(n);
}
void mrg(nd *&n,nd *l,nd *r){
    if(!l||!r) n=l?l:r;
    else if(l->p>r->p) mrg(l->r,l->r,r),n=l;
    else mrg(r->l,l,r->l),n=r;
    upd(n);
}
inline void ins(nd *&n,nd *i){
    if(!n) n=i;
    else{
        nd *l=0,*r=0;
        spt(n,l,r,i->val);
        mrg(i,i,r);
        mrg(n,l,i);
    }
}
void del(nd *&n,int i){
    if(!n) return;
    else if(n->val==i){
        nd *tmp=n;
        mrg(n,n->l,n->r);
        free(tmp);
    }else del(n->val<i?n->r:n->l,i);
    upd(n);
}
int sel(nd *n,int i){
    if(sz(n->l)+1==i) return n->val;
    else if(sz(n->l)+1<i) return sel(n->r,i-sz(n->l)-1);
    else return sel(n->l,i);
}
inline int median(nd *rt){
    return sel(rt,(sz(rt)+1)/2);
}
inline ll calc(nd *n){
    if(sz(n)<=1) return 0;
    int m=median(n);
    nd *l=0,*r=0;
    spt(n,l,r,m);
    ll res=1LL*m*sz(l)-sum(l)+sum(r)-1LL*m*sz(r);
    mrg(n,l,r);
    return res;
}
namespace k1{
    inline void solve(){
        nd *t=0;
        for(int i=0;i<N;++i){
            if(P[i].z1==P[i].z2) base+=abs(P[i].b1-P[i].b2);
            else{
                ins(t,new nd(P[i].b1));
                ins(t,new nd(P[i].b2));
            }
        }
        printf("%lld",calc(t)+base+sz(t)/2);
    }
}
namespace k2{
    inline void solve(){
        nd *t1=0,*t2=0;
        std::vector<pii>V;
        for(int i=0;i<N;++i){
            if(P[i].z1==P[i].z2) base+=abs(P[i].b1-P[i].b2);
            else{
                V.emplace_back(P[i].b1,P[i].b2);
                ins(t2,new nd(P[i].b1));
                ins(t2,new nd(P[i].b2));
            }
        }
        if(V.empty()){
            printf("%lld",base);
            return;
        }
        std::sort(all(V),[=](const pii &p1,const pii &p2){
            return p1.first+p1.second<p2.first+p2.second;
        });
        for(auto a:V){
            del(t2,a.first);
            del(t2,a.second);
            ins(t1,new nd(a.first));
            ins(t1,new nd(a.second));
            ans=std::min(ans,calc(t1)+calc(t2));
        }
        printf("%lld",ans+base+(sz(t1)+sz(t2))/2);
    }
}
int main(){
    scanf("%d%d",&K,&N);
    for(int i=0;i<N;++i)
        scanf(" %c %d %c %d",&P[i].z1,&P[i].b1,&P[i].z2,&P[i].b2);
    ans=0x3f3f3f3f3f3f3f3f;
    if(K==1) k1::solve();
    else k2::solve();
}
