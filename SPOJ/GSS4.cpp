#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e5+4;
struct sgtnd{
    int l,r;
    ll mx,sum;
}sgt[MN*3];
int N,M;
ll A[MN];
void build(int l,int r,int i){
    sgt[i].l=l;
    sgt[i].r=r;
    if(l==r)
        sgt[i].mx=sgt[i].sum=A[l];
    else{
        int mid=l+r>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        sgt[i].mx=std::max(sgt[i<<1].mx,sgt[i<<1|1].mx);
        sgt[i].sum=sgt[i<<1].sum+sgt[i<<1|1].sum;
    }
}
inline void upd(int i){
    sgt[i].mx=std::max(sgt[i<<1].mx,sgt[i<<1|1].mx);
    sgt[i].sum=sgt[i<<1].sum+sgt[i<<1|1].sum;
}
void mod(int l,int r,int i){
    if(sgt[i].r<l||sgt[i].l>r||sgt[i].mx==1) return;
    if(sgt[i].l==sgt[i].r)
        sgt[i].sum=sgt[i].mx=sqrt(sgt[i].mx);
    else{
        int mid=sgt[i].l+sgt[i].r>>1;
        if(l<=mid) mod(l,r,i<<1);
        if(r>mid) mod(l,r,i<<1|1);
        upd(i);
    }
}
ll qry(int l,int r,int i){
    if(sgt[i].r<l||sgt[i].l>r) return 0;
    if(l<=sgt[i].l&&sgt[i].r<=r) return sgt[i].sum;
    if(sgt[i].mx==1) return std::min(r,sgt[i].r)-std::max(l,sgt[i].l)+1;
    int mid=sgt[i].l+sgt[i].r>>1;
    ll res=0;
    if(l<=mid) res+=qry(l,r,i<<1);
    if(r>mid) res+=qry(l,r,i<<1|1);
    return res;
}
int main(){
    for(int tc=1;~scanf("%d",&N);++tc){
        for(int i=1;i<=N;scanf("%lld",A+i++));
        build(1,N,1);
        printf("Case #%d:\n",tc);
        scanf("%d",&M);
        for(int i=0,a,b,c;i<M;++i){
            scanf("%d%d%d",&a,&b,&c);
            if(b>c) std::swap(b,c); // wtf guys
            if(a)
                printf("%lld\n",qry(b,c,1));
            else
                mod(b,c,1);
        }
        printf("\n");
    }
}
