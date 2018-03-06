#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
typedef long long ll;
const int MN=1e5+4,MQ=1e5+4,RT=320,INF=1e9;
int N,K,Q,A[MN],pos[MN][4];
struct qry{
    int l,r,i;
    inline bool operator < (const qry &q) const {
        return l/RT<q.l/RT||(l/RT==q.l/RT&&r<q.r);
    }
}qrys[MQ];
ll res,ans[MQ],bit[MN];
std::vector<int>V;
inline void upd(int i,int v){
    for(;i<MN;i+=i&-i)
        bit[i]+=v;
}
inline ll qry(int i){
    ll res=0;
    for(;i;i-=i&-i)
        res+=bit[i];
    return res;
}
inline void add(int i){
    res+=qry(pos[i][2])-qry(pos[i][0]);
    upd(pos[i][1],1);
}
inline void rem(int i){
    upd(pos[i][1],-1);
    res-=qry(pos[i][2])-qry(pos[i][0]);
}
int main(){
    scanf("%d%d",&N,&K);
    for(int i=0;i<N;++i){
        scanf("%d",A+i);
        V.emplace_back(A[i]);
    }
    std::sort(all(V));
    V.erase(std::unique(all(V)),V.end());
    for(int i=0;i<N;++i){
        pos[i][0]=std::lower_bound(all(V),A[i]-K)-V.begin();
        pos[i][1]=std::lower_bound(all(V),A[i])-V.begin()+1;
        pos[i][2]=std::upper_bound(all(V),A[i]+K)-V.begin();
    }
    scanf("%d",&Q);
    for(int i=0,a,b;i<Q;++i){
        scanf("%d%d",&a,&b);
        qrys[i]={a,b,i};
    }
    std::sort(qrys,qrys+Q);
    for(int i=0,lst=-1,l,r;i<Q;++i){
        if(qrys[i].l/RT!=lst){
            memset(bit,0,sizeof bit);
            l=r=qrys[i].l;
            upd(pos[l][1],1);
            lst=qrys[i].l/RT;
            res=0;
        }
        while(r<qrys[i].r) add(++r);
        while(l>qrys[i].l) add(--l);
        while(l<qrys[i].l) rem(l++);
        while(r>qrys[i].r) rem(r--);
        ans[qrys[i].i]=res;
    }
    for(int i=0;i<Q;printf("%lld\n",ans[i++]));
}

