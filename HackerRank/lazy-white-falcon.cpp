#include<bits/stdc++.h>
const int MN=1e5+4,LN=18;
int N,Q,ecnt,A[MN],ein[MN],eout[MN],depth[MN],bit[MN*2],st[MN][LN];
std::vector<int>adj[MN];
void dfs(int src,int par,int d=1){
    ein[src]=++ecnt;
    depth[src]=d++;
    st[src][0]=par;
    for(int i:adj[src]){
        if(i==par) continue;
        dfs(i,src,d);
    }
    eout[src]=++ecnt;
}
inline void upd(int ind,int val){
    for(;ind<MN*2;ind+=ind&-ind) bit[ind]+=val;
}
inline int qry(int ind){
    int res=0;
    for(;ind;ind-=ind&-ind) res+=bit[ind];
    return res;
}
inline void build(){
    for(int j=1;j<LN;++j)
        for(int i=0;i<N;++i)
            st[i][j]=~st[i][j-1]?st[st[i][j-1]][j-1]:-1;
}
inline int lca(int u,int v){
    if(depth[u]<depth[v]) std::swap(u,v);
    for(int i=LN-1;~i;--i)
        if(~st[u][i]&&depth[st[u][i]]>=depth[v])
            u=st[u][i];
    if(u==v) return u;
    for(int i=LN-1;~i;--i)
        if(st[u][i]!=st[v][i])
            u=st[u][i],v=st[v][i];
    return st[u][0];
}
int main(){
    scanf("%d%d",&N,&Q);
    for(int i=1,a,b;i<N;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    memset(st,-1,sizeof st);
    dfs(0,-1);
    build();
    for(int i=0,a,b,c;i<Q;++i){
        scanf("%d%d%d",&a,&b,&c);
        if(a==1){
            upd(ein[b],c-A[b]);
            upd(eout[b],A[b]-c);
            A[b]=c;
        }else{
            int l=lca(b,c);
            printf("%d\n",qry(ein[b])+qry(ein[c])-2*qry(ein[l])+A[l]);
        }
    }
}
