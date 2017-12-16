#include<bits/stdc++.h>
#include<bits/extc++.h>
//try the space-saving segtree
typedef unsigned int uint;
const int MAXN=1e5+4,LFS=16;
uint N,Q,A[MAXN],nd[MAXN<<1];
char c;
void build(uint l,uint r,uint ind) {
    if(r-l<=LFS) {
        // leaf node
        nd[ind] = 0xffffffff;
        for(uint i=l;i<=r;nd[ind]&=A[i++]);
    } else {
        uint mid=l+r>>1;
        build(l,mid,ind<<1);
        build(mid+1,r,ind<<1|1);
        nd[ind]=nd[ind<<1]&nd[ind<<1|1];
    }
}
void upd(uint pos,uint val,uint l,uint r,uint ind) {
    if(r-l<=LFS) {
        // this is now a leaf
        nd[ind]=0xffffffff;
        for(uint i=l;i<=r;nd[ind]&=A[i++]);
    } else {
        uint mid=l+r>>1;
        if(pos<=mid) upd(pos,val,l,mid,ind<<1);
        else upd(pos,val,mid+1,r,ind<<1|1);
        nd[ind]=nd[ind<<1]&nd[ind<<1|1];
    }
}
uint qry(uint ql,uint qr,uint l,uint r,uint ind) {
    if(r-l<=LFS) {
        // brute force within leaf
        uint res=0xffffffff;
        for(uint i=ql;i<=qr;res&=A[i++]);
        return res;
    } else if(ql==l&&qr==r) return nd[ind];
    else {
        uint mid=l+r>>1;
        if(qr<=mid) return qry(ql,qr,l,mid,ind<<1);
        else if(ql>mid) return qry(ql,qr,mid+1,r,ind<<1|1);
        else return qry(ql,mid,l,mid,ind<<1)&qry(mid+1,qr,mid+1,r,ind<<1|1);
    }
}
int main() {
    scanf("%u%u",&N,&Q);
    for(uint i=1;i<=N;scanf("%u",A+i++));
    build(1,N,1);
    for(uint i=1,x,y,z;i<=Q;++i) {
        scanf(" %c",&c);
        if(c=='Q') {
            scanf("%u%u%u",&x,&y,&z);
            printf("%u\n",z&qry(x,y,1,N,1));
        } else {
            scanf("%u%u",&x,&y);
            A[x]=y;
            upd(x,y,1,N,1);
        }
    }
}
