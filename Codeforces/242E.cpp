#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e5+4;
int N,Q,A[MN];
struct bits{
    int cnt[32];
    bits():cnt{0}{}
    bits(int val){
        for(int i=0;i<31;++i)
            cnt[i]=bool(val&(1<<i));
    }
    inline int& operator [] (const int i){
        return cnt[i];
    }
    inline bits operator + (bits b){
        bits res=bits();
        for(int i=0;i<31;++i)
            res[i]=cnt[i]+b[i];
        return res;
    }
    inline ll eval() const{
        ll res=0;
        for(int i=0;i<31;++i)
            res+=1LL*cnt[i]<<i;
        return res;
    }
};
struct sgnd{
    int l,r,lz;
    bits b;
}sgt[MN*3];
void build(int l,int r,int i){
    sgt[i].l=l;
    sgt[i].r=r;
    if(l==r){
        sgt[i].b=bits(A[l]);
    }else{
        int mid=l+r>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        sgt[i].b=sgt[i<<1].b+sgt[i<<1|1].b;
    }
}
inline void _mod(int v,int i){
    for(int j=0;j<31;++j)
        if(v&(1<<j))
            sgt[i].b[j]=sgt[i].r-sgt[i].l+1-sgt[i].b[j];
}
inline void psh(int i){
    if(!sgt[i].lz) return;
    if(sgt[i].l!=sgt[i].r){
        _mod(sgt[i].lz,i<<1);
        sgt[i<<1].lz^=sgt[i].lz;
        _mod(sgt[i].lz,i<<1|1);
        sgt[i<<1|1].lz^=sgt[i].lz;
    }
    sgt[i].lz=0;
}
inline void upd(int i){
    if(sgt[i].l==sgt[i].r) return;
    sgt[i].b=sgt[i<<1].b+sgt[i<<1|1].b;
}
void mod(int l,int r,int v,int i){
    if(sgt[i].l>r||sgt[i].r<l) return;
    if(l<=sgt[i].l&&sgt[i].r<=r){
        _mod(v,i);
        sgt[i].lz^=v;
        return;
    }
    psh(i);
    int mid=sgt[i].l+sgt[i].r>>1;
    if(l<=mid) mod(l,r,v,i<<1);
    if(r>mid) mod(l,r,v,i<<1|1);
    upd(i);
}
bits qry(int l,int r,int i){
    if(sgt[i].l>r||sgt[i].r<l) return bits();
    if(l<=sgt[i].l&&sgt[i].r<=r) return sgt[i].b;
    psh(i);
    int mid=sgt[i].l+sgt[i].r>>1;
    bits res=bits();
    if(l<=mid) res=res+qry(l,r,i<<1);
    if(r>mid) res=res+qry(l,r,i<<1|1);
    return res;
}
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;scanf("%d",A+i++));
    build(1,N,1);
    scanf("%d",&Q);
    for(int i=0,a,b,c,d;i<Q;++i){
        scanf("%d%d%d",&a,&b,&c);
        if(a==1)
            printf("%lld\n",qry(b,c,1).eval());
        else{
            scanf("%d",&d);
            mod(b,c,d,1);   
        }
    }
}
