#include<bits/stdc++.h>
typedef std::pair<int,int>pii;
const int MN=1e5+4,LN=17;
int Q,depth[MN],st[MN][LN];
pii dia[MN];
char c;
inline int rt(int u){
    for(int i=LN-1;~i;--i)
        if(~st[u][i])
            u=st[u][i];
    return u;
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
inline int dist(int u,int v){
    return depth[u]+depth[v]-2*depth[lca(u,v)];
}
int main(){
    freopen("newbarn.in","r",stdin);
    freopen("newbarn.out","w",stdout);
    scanf("%d",&Q);
    memset(st,-1,sizeof st);
    for(int i=1,n=1,a;i<=Q;++i){
        scanf(" %c%d",&c,&a);
        if(c=='B'){
            if(~a){
                depth[n]=depth[a]+1;
                st[n][0]=a;
                for(int j=1;j<LN;++j)
                    st[n][j]=~st[n][j-1]?st[st[n][j-1]][j-1]:-1;
                pii &p=dia[rt(n)];
                if(dist(p.first,p.second)<dist(p.first,n))
                    p.second=n;
                if(dist(p.first,p.second)<dist(n,p.second))
                    p.first=n;
            }else{
                depth[n]=1;
                dia[n]={n,n};
            }
            ++n;
        }else{
            pii p=dia[rt(a)];
            printf("%d\n",std::max(dist(p.first,a),dist(a,p.second)));
        }
    }
}
