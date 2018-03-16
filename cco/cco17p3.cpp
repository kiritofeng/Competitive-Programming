#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
typedef long long ll;
const int MQ=2e5+4;
int N,Q;
ll ans[MQ];
struct nd{
    int p;
    ll key,val,sum;
    nd *l,*r;
    nd(ll u1,ll u2):p(rand()),key(u1),val(u2),sum(u2),l(0),r(0){}
}*rt;
struct evt{
    ll x,y1,y2,v;
    evt(ll a,ll b,ll c,ll d):x(a),y1(b),y2(c),v(d){}
    inline bool operator < (const evt &e) const{
        return x<e.x;
    }
};
std::vector<evt>evts;
struct qry{
    ll x,y;
    int i;
    qry(ll a,ll b,int c):x(a),y(b),i(c){}
    inline bool operator < (const qry &q){
        return x<q.x;
    }
};
std::vector<qry>qrys;
inline ll rev(ll u){
    ll res=0;
    for(ll i=0;i<62;++i)
        if(u&(1LL<<i))
            res|=(1LL<<(61-i));
    return res;
}
inline ll st(ll u){
    return u-(u&-u);
}
inline ll ed(ll u){
    return u-(u&-u)+((u&-u)<<1LL);
}
inline ll sum(nd *n){
    return n?n->sum:0;
}
inline void upd(nd *n){
    if(!n) return;
    n->sum=sum(n->l)+n->val+sum(n->r);
}
void spt(nd *n,nd *&l,nd *&r,ll key){
    if(!n) l=r=0;
    else if(n->key<=key) spt(n->r,n->r,r,key),l=n;
    else spt(n->l,l,n->l,key),r=n;
    upd(n);
}
void mrg(nd *&n,nd *l,nd *r){
    if(!l||!r) n=l?l:r;
    else if(l->p>r->p) mrg(l->r,l->r,r),n=l;
    else mrg(r->l,l,r->l),n=r;
    upd(n);
}
void ins(nd *&n,nd *i){
    if(!n)n=i;
    else if(i->p>n->p) spt(n,i->l,i->r,i->key),n=i;
    else ins(n->key<=i->key?n->r:n->l,i);
    upd(n);
}
int main(){
    scanf("%d%d",&N,&Q);
    for(int i=0;i<N;++i){
        ll a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        a=rev(a),b=rev(b);
        evts.emplace_back(st(a)+1,st(b)+1,ed(b),c);
        evts.emplace_back(ed(a),st(b)+1,ed(b),-c);
    }
    std::sort(all(evts));
    for(int i=0;i<Q;++i){
        ll a,b;
        scanf("%lld%lld",&a,&b);
        qrys.emplace_back(rev(a),rev(b),i);
    }
    std::sort(all(qrys));
    int i=0;
    for(qry &q:qrys){
        while(i<evts.size()&&evts[i].x<=q.x){
            ins(rt,new nd(evts[i].y1,evts[i].v));
            ins(rt,new nd(evts[i].y2,-evts[i].v));
            ++i;
        }
        nd *l=0,*r=0;
        spt(rt,l,r,q.y);
        ans[q.i]=sum(l);
        mrg(rt,l,r);
    }
    for(int i=0;i<Q;printf("%lld\n",ans[i++]));
}
