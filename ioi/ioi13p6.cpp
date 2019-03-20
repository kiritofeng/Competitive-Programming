#include<bits/stdc++.h>
typedef long long ll;
typedef std::pair<int,int>pii;
int R,C;
void init(int _R,int _C) {
    std::tie(R,C) = std::make_pair(_R,_C);
}
// SBT it is
struct nd{
    int sz,mn,mx;
    ll val,res;
    pii i;
    nd *ch[2];
    nd(int x,int y,ll K):sz(1),mn(x),mx(x),val(K),res(K),i{x,y},ch{0}{}
};
struct sgt{
    nd *t;
    sgt *ch[2];
    sgt():t(0),ch{0}{};
}*rt;
inline ll gcd(ll a,ll b) {
    while(a && b) a > b ? a %= b : b %= a;
    return a|b;
}
inline int sz(nd *n) {
    return n?n->sz:0;
}
inline void upd(nd *n) {
    if(!n) return;
    n->res=n->val;
    n->mx=n->mn=n->i.first;
    n->sz=1;
    if(n->ch[0]) {
        n->sz+=n->ch[0]->sz;
        n->res=gcd(n->res,n->ch[0]->res);
        n->mn=n->ch[0]->mn;
    }
    if(n->ch[1]) {
        n->sz+=n->ch[1]->sz;
        n->res=gcd(n->res,n->ch[1]->res);
        n->mx=n->ch[1]->mx;
    }
}
inline void rot(nd *&n,bool b) {
    nd *c=n->ch[b];
    n->ch[b]=c->ch[!b];
    c->ch[!b]=n;
    upd(n);
    upd(c);
    n=c;
}
void mtn(nd *&n,bool b) {
    if(!n||!n->ch[b]) return;
    if(sz(n->ch[!b])<sz(n->ch[b]->ch[!b])) {
        rot(n->ch[b],!b);
        rot(n,b);
    } else if(sz(n->ch[!b])<sz(n->ch[b]->ch[b])) {
        rot(n,b);
    } else return;
    mtn(n->ch[0],0);
    mtn(n->ch[1],1);
    mtn(n,0);
    mtn(n,1);
}
void ins(nd *&n,nd *i) {
    if(!n) n=i;
    else {
        bool b=n->i<i->i;
        ins(n->ch[b],i);
        upd(n);
        mtn(n,b);
    }
}
void del(nd *&n,pii p) {
    if(!n) return;
    if(n->i==p) {
        if(!n->ch[0]||!n->ch[1])
            n=n->ch[0]?n->ch[0]:n->ch[1];
        else {
            rot(n,0);
            del(n->ch[1],p);
        }
    }else del(n->ch[n->i<p],p);
    upd(n);
}
ll qry(nd *n,int l,int r) {
    if(!n or n->mn > r or n->mx < l) return 0;
    if(l <= n->mn and n->mx <= r)
        return n->res;
    ll ret = l<=n->i.first and n->i.first<=r ? n->val : 0;
    ret = gcd(gcd(qry(n->ch[0],l,r),qry(n->ch[1],l,r)),ret);
    return ret;
}
void update(sgt *&s,int P,int Q,ll K,int l,int r) {
    if(!s) s = new sgt();
    del(s->t,std::make_pair(Q,P));
    ins(s->t,new nd(Q,P,K));
    if(l==r) return;
    int mid=l+r>>1;
    if(P<=mid) update(s->ch[0],P,Q,K,l,mid);
    else update(s->ch[1],P,Q,K,mid+1,r);
}
void update(int P,int Q, ll K) {
    update(rt,P,Q,K,0,R-1);
}
ll calculate(sgt *s,int P,int Q,int U,int V,int l,int r) {
    if(!s or P > r or U < l)
        return 0;
    if(P <= l and r <= U) {
        return qry(s->t,Q,V);
    }
    int mid=l+r>>1;
    return gcd(calculate(s->ch[0],P,Q,U,V,l,mid),calculate(s->ch[1],P,Q,U,V,mid+1,r));
}
ll calculate(int P,int Q,int U,int V) {
    return calculate(rt,P,Q,U,V,0,R-1);
}
#ifndef SIGNATURE_GRADER
int N;
int main() {
    scanf("%d%d%d",&R,&C,&N);
    for(ll i=0,a,b,c,d,e,res;i<N;++i) {
        scanf("%lld",&a);
        if(a&1) {
            scanf("%lld%lld%lld",&b,&c,&d);
            update(b,c,d);
        } else {
            scanf("%lld%lld%lld%lld",&b,&c,&d,&e);
            printf("%lld\n", res=calculate(b,c,d,e));
        }
    }
}
#endif
