#include<bits/stdc++.h>
typedef long long ll;
const int MN=2e5+4;
int N,A[MN];
ll ans;
struct nd{
    int l,r,val;
    nd *ch[2];
    nd():l(0),r(0),val(0),ch{0}{}
    nd(nd *n):l(n->l),r(n->r),val(n->val){ch[0]=n->ch[0],ch[1]=n->ch[1];}
}*sgt[MN];
inline void upd(nd *n){
    n->val=n->ch[0]->val+n->ch[1]->val;
}
void build(nd *&n,int l,int r){
    n=new nd();
    n->l=l;
    n->r=r;
    if(l==r) return;
    int mid=l+r>>1;
    build(n->ch[0],l,mid);
    build(n->ch[1],mid+1,r);
}
void mod(nd *&n,nd *o,int p){
    n=new nd(o);
    if(n->l==n->r){
        ++n->val;
        return;
    }
    int mid=n->l+n->r>>1;
    bool b=p>mid;
    n->ch[b]=0;
    mod(n->ch[b],o->ch[b],p);
    upd(n);
}
int qry(nd *n,int p){
    if(n->l==n->r) return n->val;
    int mid=n->l+n->r>>1;
    bool b=p>mid;
    if(b) return qry(n->ch[1],p);
    else return qry(n->ch[0],p)+n->ch[1]->val;
}
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;scanf("%d",A+i++));
    build(sgt[0],1,N);
    for(int i=1;i<=N;++i)
        mod(sgt[i],sgt[i-1],std::min(A[i],N));
    for(int i=1;i<=N;++i){
        ans+=qry(sgt[std::min(A[i],N)],i);
        if(A[i]>=i) --ans;
    }
    printf("%lld\n",ans>>1);
}
