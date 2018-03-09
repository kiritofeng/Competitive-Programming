#include<bits/stdc++.h>
typedef long long ll;
const int MN=36;
int N;
ll A,B,ans,arr[MN];
struct nd{
    int p;
    ll val,cnt,sum;
    nd *l,*r;
    nd(ll v):val(v),p(rand()),cnt(1),sum(1),l(0),r(0){}
}*rt;
inline ll cnt(nd *n){
    return n?n->cnt:0;
}
inline ll sum(nd *n){
    return n?n->sum:0;
}
inline void upd(nd *n){
    if(!n) return;
    n->sum=sum(n->l)+n->cnt+sum(n->r);
}
void spt(nd *n,nd *&l,nd *&r,ll key){
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
inline void add(ll v){
    nd *l=0,*m=0,*r=0,*tmp=0;
    spt(rt,l,tmp,v-1);
    spt(tmp,m,r,v);
    if(!m) m=new nd(v);
    else{m->cnt+=1,m->sum+=1;}
    mrg(tmp,m,r);
    mrg(rt,l,tmp);
}
inline ll qry(ll v){
    nd *l=0,*m=0,*r=0,*tmp=0;
    spt(rt,l,tmp,A-v-1);
    spt(tmp,m,r,B-v);
    ll res=sum(m);
    mrg(tmp,m,r);
    mrg(rt,l,tmp);
    return res;
}
void dfs1(int i,ll sum=0){
    if(!i) add(sum);
    else{
        dfs1(i-1,sum+arr[i]);
        dfs1(i-1,sum);
    }
}
void dfs2(int i,ll sum=0){
    if(i>N) ans+=qry(sum);
    else{
        dfs2(i+1,sum+arr[i]);
        dfs2(i+1,sum);
    }
}
int main(){
    scanf("%d%lld%lld",&N,&A,&B);
    for(int i=1;i<=N;scanf("%lld",arr+i++));
    dfs1(N/2);
    dfs2(N/2+1);
    printf("%lld\n",ans);
}
