#include<bits/stdc++.h>
const int MN=1e5+4,INF=0x3f3f3f3f;
int N,R,M,ans,D,A[MN],depth[MN],ord[MN],ecnt,ein[MN],eout[MN],ed[MN];
std::vector<int>adj[MN];
struct nd{
    int l,r,val;
    nd *ch[2];
    nd():l(0),r(0),val(INF),ch{0}{}
}*sgt[MN];
void dfs(int src,int p,int d){
    depth[src]=d;
    ein[src]=++ecnt;
    for(int i:adj[src]){
        if(i==p) continue;
        dfs(i,src,d+1);
    }
    eout[src]=ecnt;
}
inline void upd(nd *n){
    n->val=std::min(n->ch[0]->val,n->ch[1]->val);
}
void build(nd *&n,int l,int r){
    n=new nd();
    n->l=l,n->r=r;
    if(l==r) return;
    int mid=l+r>>1;
    build(n->ch[0],l,mid);
    build(n->ch[1],mid+1,r);
}
void mod(nd *&n,nd *o,int p,int v){
    n=new nd();
    n->l=o->l,n->r=o->r;
    if(n->l==n->r){
        n->val=v;
        return;
    }
    int mid=n->l+n->r>>1;
    bool b=p>mid;
    n->ch[!b]=o->ch[!b];
    mod(n->ch[b],o->ch[b],p,v);
    upd(n);
}
int qry(nd *n,int l,int r){
    if(l>n->r||r<n->l) return INF;
    if(l<=n->l&&n->r<=r) return n->val;
    return std::min(qry(n->ch[0],l,r),qry(n->ch[1],l,r));
}
int main(){
    scanf("%d%d",&N,&R);
    for(int i=1;i<=N;scanf("%d",A+i++));
    for(int i=1,a,b;i<N;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    dfs(R,-1,1);
    for(int i=0;i<N;++i) ord[i]=i+1;
    std::stable_sort(ord,ord+N,[=](const int &a,const int &b){
        return depth[a]<depth[b];
    });
    build(sgt[0],1,N);
    for(int i=0;i<N;++i){
        if(depth[ord[i]]!=D) ed[D++]=i;
        mod(sgt[i+1],sgt[i],ein[ord[i]],A[ord[i]]);
    }
    st[D]=N;
    scanf("%d",&M);
    for(int i=0,a,b;i<M;++i){
        scanf("%d%d",&a,&b);
        a=((a+ans)%N)+1,b=(b+ans)%N;
        printf("%d\n",ans=qry(sgt[ed[std::min(depth[a]+b,D)]],ein[a],eout[a]));
    }
}
