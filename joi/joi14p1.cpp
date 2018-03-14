#include <bits/stdc++.h>
typedef long long ll;
typedef std::pair<int,int>pii;
const int MN=5e5+4,LN=20;
const ll LINF=0x3f3f3f3f3f3f3f3f;
int N,Q,qcnt,sz[MN],cen[MN],cenpar[MN],ord[MN],tim[MN];
std::vector<pii>adj[MN];
ll ans[MN],dist[MN][LN];
void dfs1(int src,int par){
    sz[src]=1;
    for(pii &p:adj[src]){
        if(p.first==par) continue;
        dfs1(p.first,src);
        sz[src]+=sz[p.first];
    }
}
void centroid(int src,int pre,int l,int s){
    if(cen[src]) return;
    for(pii &p1:adj[src]){
        if(cen[p1.first]) continue;
        if(sz[p1.first]>s/2){
            sz[src]=1;
            for(pii &p2:adj[src]){
                if(cen[p2.first]||p2.first==p1.first) continue;
                sz[src]+=sz[p2.first];
            }
            centroid(p1.first,pre,l,s);
            return;
        }
    }
    cenpar[src]=pre;
    cen[src]=l;
    for(pii &p1:adj[src]){
        if(cen[p1.first]) continue;
        centroid(p1.first,src,l+1,sz[p1.first]);
    }
}
void dfs2(int src,int par,int l,ll d=0){
    dist[src][l]=d;
    for(pii &p1:adj[src]){
        if(p1.first==par||cen[p1.first]<l) continue;
        dfs2(p1.first,src,l,d+p1.second);
    }
}
void Init(int _N,int* _A,int* _B,int* _D) {
    N=_N;
    for(int i=0;i<N-1;++i) {
        adj[_A[i]].emplace_back(_B[i],_D[i]);
        adj[_B[i]].emplace_back(_A[i],_D[i]);
    }
    dfs1(0,-1);
    centroid(0,-1,1,N);
    for(int i=0;i<N;++i) ord[i]=i;
    std::stable_sort(ord,ord+N,[=](const int &a,const int &b){
        return cen[a]<cen[b];
    });
    for(int i=0,c;i<N;++i){
        c=ord[i];
        dfs2(c,-1,cen[c]);
    }
}
ll Query(int _S,int* _X,int _T,int* _Y) {
    ll res=LINF;
    ++qcnt;
    std::stable_sort(_X,_X+_S);
    for(int i=0,j;i<_S;++i) {
        j=_X[i];
        while(~j){
            if(tim[j]<qcnt)ans[j]=LINF;
            tim[j]=qcnt;
            ans[j]=std::min(ans[j],dist[_X[i]][cen[j]]);
            j=cenpar[j];
        }
    }
    std::stable_sort(_Y,_Y+_T);
    for(int i=0,j;i<_T;++i){
        j=_Y[i];
        while(~j){
            if(tim[j]<qcnt)ans[j]=LINF;
            tim[j]=qcnt;
            res=std::min(res,ans[j]+dist[_Y[i]][cen[j]]);
            j=cenpar[j];
        }
    }
    return res;
}
