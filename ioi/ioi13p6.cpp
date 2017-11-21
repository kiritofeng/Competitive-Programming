#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
struct treapnd {
    pii ind;
    int p;
    ll val,res;
    treapnd *l,*r;
    treapnd(int i,int j,ll v):p(rand()),val(v),res(v),l(0),r(0){ind.first=i,ind.second=j;}
};
struct segnd {
    treapnd *t;
    segnd *l,*r;
    segnd():t(0),l(0),r(0){}
}*root;
int R,C;
inline ll gcd(ll a,ll b) {
    while(a&&b)a>b?a%=b:b%=a;
    return a|b;
}
inline ll res(treapnd *t) {
    return t?t->res:0;
}
inline void upd(treapnd *t) {
    if(t) t->res=gcd(t->val,gcd(res(t->l),res(t->r)));
}
void split(treapnd *t,treapnd *&l,treapnd *&r,pii key) {
    if(!t) l=r=0;
    else if(t->ind<=key) split(t->r,t->r,r,key),l=t;
    else split(t->l,l,t->l,key),r=t;
    upd(t);
}
void merge(treapnd *&t,treapnd *l,treapnd *r) {
    if(!l||!r)t=l?l:r;
    else if(l->p>r->p) merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    upd(t);
}
void treapins(treapnd *&t,treapnd *n) {
    if(!t) t=n;
    else if(n->p>t->p) split(t,n->l,n->r,n->ind),t=n;
    else treapins(n->ind<t->ind?t->l:t->r,n);
    upd(t);
}
void treapdel(treapnd *&t,pii val) {
    if(!t) return;
    else if(t->ind==val) {
        treapnd *tmp=t;
        merge(t,t->l,t->r);
        free(tmp);
    } else treapdel(val<=t->ind?t->l:t->r,val);
}
ll treapqry(treapnd *t,int Q,int V) {
    if(!t) return 0;
    treapnd *l=0,*m=0,*r=0;
    split(t,m,r,make_pair(V,R-1));
    split(m,l,m,make_pair(Q-1,R-1));
    ll ans=res(m);
    merge(m,l,m);
    merge(t,m,r);
    return ans;
}
void sgupd(segnd *&s,int P,int Q,ll K,int l=0,int r=R-1) {
    if(!s)
        s=new segnd();
    else
        treapdel(s->t,make_pair(Q,P));
    treapins(s->t,new treapnd(Q,P,K));
    if(l^r) {
        int mid=l+r>>1;
        if(P<=mid) sgupd(s->l,P,Q,K,l,mid);
        else sgupd(s->r,P,Q,K,mid+1,r);
    }
}
ll sgqry(segnd *s,int P,int Q,int U,int V,int l=0,int r=R-1) {
    if(!s) return 0;
    if(P==l&&U==r)
        return treapqry(s->t,Q,V);
    else {
        int mid=l+r>>1;
        if(U<=mid) return sgqry(s->l,P,Q,U,V,l,mid);
        else if(P>mid) return sgqry(s->r,P,Q,U,V,mid+1,r);
        else return gcd(sgqry(s->l,P,Q,mid,V,l,mid),sgqry(s->r,mid+1,Q,U,V,mid+1,r));
    }
}
void init(int _R,int _C) {
    R=_R;
    C=_C;
}
void update(int P,int Q,ll K) {
    sgupd(root,P,Q,K);
}
ll calculate(int P,int Q,int U,int V) {
    return sgqry(root,P,Q,U,V);
}
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
            printf("%lld\n", calculate(b,c,d,e));
        }
    }
}
