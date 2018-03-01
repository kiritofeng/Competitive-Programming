#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e5+4;
const ll INF=0x3f3f3f3f3f3f3f3f;
int N,cnt[MN];
char S[MN][20];
ll ans=INF,len[MN],ch[MN];
std::vector<int>adj[MN];
void dfs1(int src){
    for(int i:adj[src]){
        if(!cnt[i]){
            len[src]+=strlen(S[i]);
            ++ch[src];
        }else{
            dfs1(i);
            ch[src]+=ch[i];
            len[src]+=ch[i]*(strlen(S[i])+1)+len[i];
        }
    }
}
void dfs2(int src,int out=0,ll outsum=0,ll res=0LL){
    ans=std::min(ans,3LL*outsum+res+len[src]);
    for(int i:adj[src]){
        if(!cnt[i]) continue;
        dfs2(i,out+ch[src]-ch[i],outsum+out+ch[src]-ch[i],res+len[src]-len[i]-ch[i]*(strlen(S[i])+1));
    }
}
int main(){
    freopen("dirtraverse.in","r",stdin);
    freopen("dirtraverse.out","w",stdout);
    scanf("%d",&N);
    for(int i=1;i<=N;++i){
        scanf("%s%d",S[i],&cnt[i]);
        for(int j=0,a;j<cnt[i];++j){
            scanf("%d",&a);
            adj[i].emplace_back(a);
        }
    }
    dfs1(1);
    dfs2(1);
    printf("%lld\n",ans);
}
