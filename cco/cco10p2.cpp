#include<bits/stdc++.h>
const int MN=304,INF=0x3f3f3f3f;
int N,D,col[MN],ch[MN][2],nch[MN],dp[MN][MN<<1];
void dfs(int src){
    int c=2*col[src]-1;
    dp[src][c+MN]=nch[src];
    dp[src][MN]=1;
    if(!nch[src]) return;
    for(int i=0;i<nch[src];++i) dfs(ch[src][i]);
    for(int i=-N;i<=N;++i)
        for(int j=-N;j<=N;++j){
            if(c+i<-N||c+i>N) continue;
            if(i-j<-N||i-j>N) continue;
            if(i+j<-N||i+j>N) continue;
            for(int k=0;k<nch[src];++k)
                dp[src][c+i+MN]=std::min(dp[src][c+i+MN],
                                         dp[ch[src][k]][j+MN]+dp[ch[src][k^1]][i-j+MN]);
        }
    if(nch[src]>1)
        for(int i=0;i<=1;++i)
            for(int j=-N;j<=N;++j){
                if(c+j<-N||c+j>N) continue;
                dp[src][c+j+MN]=std::min(dp[src][c+j+MN],
                                         dp[ch[src][i]][j+MN]+1);
            }
}
int main(){
    scanf("%d%d",&N,&D);
    for(int i=0,a,b,c;i<N;++i){
        scanf("%d%d%d",&a,&b,&c);
        nch[a+1]=c;
        col[a+1]=b;
        for(int j=0,d;j<c;++j){
            scanf("%d",&d);
            ch[a+1][j]=d+1;
        }
    }
    memset(dp,0x3f,sizeof dp);
    dp[0][MN]=0;
    dfs(1);
    printf("%d",dp[1][D+MN]==INF?-1:dp[1][D+MN]);
}
