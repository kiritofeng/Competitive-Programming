#include<bits/stdc++.h>
#include<bits/extc++.h>
const int MAXN=3e4+4,INF=0x3f3f3f3f;
int N,Q,h,st[MAXN<<1],lz[MAXN];
inline void apply(int ind,int val) {
    st[ind]=std::max(st[ind]-val,0);
    if(ind<N) lz[ind]+=val;
}
inline void build() {
    for(int i=N-1;i;--i) st[i]=std::min(st[i<<1],st[i<<1|1]);
}
inline void build(int ind) {
    while(ind>>=1)st[ind]=std::max(std::min(st[ind<<1],st[ind<<1|1])-lz[ind],0);
}
inline void upd(int l,int r,int v) {
    for(int ll=l+=N,rr=r+=N;ll<rr;ll>>=1,rr>>=1) {
        if(ll&1) apply(ll++,v);
        if(rr&1) apply(--rr,v);
    }
    build(l);
    build(r-1);
}
inline void push(int ind) {
    for(int s=h;s;--s) {
        int i=ind>>s;
        if(lz[i]) {
            apply(i<<1,lz[i]);
            apply(i<<1|1,lz[i]);
            lz[i]=0;
        }
    }
}
inline int query(int l, int r) {
    l+=N,r+=N;
    push(l);
    push(r-1);
    int res=INF;
    for(;l<r;l>>=1,r>>=1) {
        if(l&1) res=std::min(res,st[l++]);
        if(r&1) res=std::min(res,st[--r]);
    }
    return res;
}
int main() {
    scanf("%d%d",&N,&Q);
    h=8*sizeof(int)-__builtin_clz(N);
    for(int i=0;i<N;scanf("%d",st+N+i++));
    build();
    for(int i=0,a,b,c;i<Q;++i) {
        scanf("%d%d%d",&a,&b,&c);
        upd(a-1,b,c);
        printf("%d %d\n",query(a-1,b),query(0,N));
    }
}
