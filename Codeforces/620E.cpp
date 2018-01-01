#pragma GCC optimize "Ofast"
#include<bits/stdc++.h>
#include<bits/extc++.h>
typedef long long ll;
const int MN=4e5+4;
int N,M,tcnt,ecnt,eid[MN],C[MN],ein[MN],eout[MN];
ll st[MN*3],lz[MN*3];
std::vector<int>adj[MN];
void dfs(int src,int par){
    eid[ein[src]=++tcnt]=src;
    for(int i:adj[src]){
        if(i==par) continue;
        dfs(i,src);
    }
    eout[src]=tcnt;
}
void pshd(int ind){
    st[ind<<1]=lz[ind<<1]=lz[ind];
    st[ind<<1|1]=lz[ind<<1|1]=lz[ind];
    lz[ind]=0;
}
void build(int l,int r,int ind){
    if(l==r){
        st[ind]=1LL<<C[eid[l]];
    }else{
        int mid=l+r>>1;
        build(l,mid,ind<<1);
        build(mid+1,r,ind<<1|1);
        st[ind]=st[ind<<1]|st[ind<<1|1];
    }
}
void upd(int ql,int qr,int c,int l,int r,int ind){
    if(ql==l&&qr==r){
        st[ind]=1LL<<c;
        lz[ind]=1LL<<c;
        return;
    }
    if(lz[ind])
        pshd(ind);
    int mid=l+r>>1;
    if(qr<=mid)
        upd(ql,qr,c,l,mid,ind<<1);
    else if(ql>mid)
        upd(ql,qr,c,mid+1,r,ind<<1|1);
    else
        upd(ql,mid,c,l,mid,ind<<1),upd(mid+1,qr,c,mid+1,r,ind<<1|1);
    st[ind]=st[ind<<1]|st[ind<<1|1];
}
ll qry(int ql,int qr,int l,int r,int ind){
    if(ql==l&&qr==r) return st[ind];
    if(lz[ind])
        pshd(ind);
    int mid=l+r>>1;
    if(qr<=mid) return qry(ql,qr,l,mid,ind<<1);
    else if(ql>mid) return qry(ql,qr,mid+1,r,ind<<1|1);
    else return qry(ql,mid,l,mid,ind<<1)|qry(mid+1,qr,mid+1,r,ind<<1|1);
}
int main(){
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;scanf("%d",C+i++));
    for(int i=1,a,b;i<N;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    dfs(1,1);
    build(1,tcnt,1);
    for(int i=0,a,b,c;i<M;++i){
        scanf("%d",&a);
        if(a==1){
            scanf("%d%d",&b,&c);
            upd(ein[b],eout[b],c,1,tcnt,1);
        }else{
            scanf("%d",&b);
            printf("%d\n",__builtin_popcountll(qry(ein[b],eout[b],1,tcnt,1)));
        }
    }
}
