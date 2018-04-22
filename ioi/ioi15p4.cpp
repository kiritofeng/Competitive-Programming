#include<bits/stdc++.h>
typedef std::pair<int,int>pii;
const int MN=5e5+4,MOD=1e9+7;
int N,*X,*Y;
struct nd{
    int l,r,b;
    pii pre,suf,tot;
}sgt[MN*3];
inline pii _upd(pii l,pii r){
    pii res={int((1LL*l.first*r.first)%MOD),0};
    res.second=(l.second||r.second||1LL*l.first*r.first>MOD);
    return res;
}
inline void upd(int i){
    pii tmp=_upd(sgt[i<<1].suf,sgt[i<<1|1].pre);
    if(tmp.second||1LL*tmp.first*Y[sgt[i<<1|1].b]>Y[sgt[i<<1].b]){
        sgt[i].b=sgt[i<<1|1].b;
        sgt[i].suf=sgt[i<<1|1].suf;
        sgt[i].pre=_upd(sgt[i<<1].tot,sgt[i<<1|1].pre);
    }else{
        sgt[i].b=sgt[i<<1].b;
        sgt[i].pre=sgt[i<<1].pre;
        sgt[i].suf=_upd(sgt[i<<1].suf,sgt[i<<1|1].tot);
    }
    sgt[i].tot=_upd(sgt[i<<1].tot,sgt[i<<1|1].tot);
}
void build(int l,int r,int i){
    sgt[i].l=l,sgt[i].r=r;
    if(l==r){
        sgt[i].b=l;
        sgt[i].pre={X[l],0};
        sgt[i].suf={1,0};
        sgt[i].tot={X[l],0};
        return;
    }
    int mid=l+r>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    upd(i);
}
void mod1(int p,int v,int i){
    if(sgt[i].l==sgt[i].r){
        sgt[i].pre=sgt[i].tot={v,0};
        return;
    }
    int mid=sgt[i].l+sgt[i].r>>1;
    if(p<=mid) mod1(p,v,i<<1);
    else mod1(p,v,i<<1|1);
    upd(i);
}
inline void mod2(int p,int i){
    if(sgt[i].l==sgt[i].r) return;
    int mid=sgt[i].l+sgt[i].r>>1;
    if(p<=mid) mod2(p,i<<1);
    else mod2(p,i<<1|1);
    upd(i);
}
inline int qry(){
    return int((1LL*sgt[1].pre.first*Y[sgt[1].b])%MOD);
}
int init(int _N,int* _X,int* _Y){
    N=_N;
    X=_X;
    Y=_Y;
    build(0,N-1,1);
    return qry();
}
int updateX(int pos,int val){
    mod1(pos,val,1);
    mod2(pos,1);
    return qry();
}
int updateY(int pos,int val){
    Y[pos]=val;
    mod2(pos,1);
    return qry();
}
#ifndef SIGNATURE_GRADER
int _N,_M,_X[MN],_Y[MN];
int main(){
    scanf("%d",&_N);
    for(int i=0;i<_N;scanf("%d",_X+i++));
    for(int i=0;i<_N;scanf("%d",_Y+i++));
    printf("%d\n",init(_N,_X,_Y));
    scanf("%d",&_M);
    for(int i=0,a,b,c;i<_M;++i){
        scanf("%d%d%d",&a,&b,&c);
        if(a==1) printf("%d\n",updateX(b,c));
        else printf("%d\n",updateY(b,c));
    }
}
#endif
