#include<bits/stdc++.h>
const int MN=104,INF=0x3f3f3f3f;
int N,L[MN],memo[MN][MN][MN];
int dp(int lft,int ind,int lst){
    if(lft<0) return INF;
    if(ind==N) return lft?INF:0;
    if(~memo[lft][ind][lst]) return memo[lft][ind][lst];
    if(!ind) return dp(lft-1,1,0)+(L[ind]!=0);
    return memo[lft][ind][lst]=std::min(dp(lft-1,ind+1,ind)+(L[ind]!=0),dp(lft,ind+1,lst)+(L[ind]!=ind-lst));
}
int main(){
    freopen("taming.in","r",stdin);
    freopen("taming.out","w",stdout);
    scanf("%d",&N);
    for(int i=0;i<N;scanf("%d",L+i++));
    memset(memo,-1,sizeof memo);
    for(int i=1;i<=N;++i)
        printf("%d\n",dp(i,0,0));
}
