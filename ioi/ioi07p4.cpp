#include<bits/stdc++.h>
const int MN=1e5+4;
int N,ans,dp[2][16][16];
char S[MN];
inline int cvt(char c){
    if(c=='M') return 1;
    if(c=='F') return 2;
    if(c=='B') return 3;
    assert(0);
}
inline int nxt(int p,int c){
    return (p<<2|c)&15;
}
inline int calc(int p,int c){
    int a=p>>2,b=p&3;
    if(!a){
        if(!b) return 1;
        else return b==c?1:2;
    }else{
        if(a==b) return b==c?1:2;
        else return a==c||b==c?2:3;
    }
}
int main(){
    scanf("%d",&N);
    scanf("%s",S+1);
    memset(dp,0xaf,sizeof dp);
    dp[0][0][0]=0;
    for(int i=1,b=1;i<=N;++i,b^=1)
        for(int j=0;j<16;++j)
            for(int k=0;k<16;++k){
                dp[b][nxt(j,cvt(S[i]))][k]=std::max(dp[b][nxt(j,cvt(S[i]))][k],dp[!b][j][k]+calc(j,cvt(S[i])));
                dp[b][j][nxt(k,cvt(S[i]))]=std::max(dp[b][j][nxt(k,cvt(S[i]))],dp[!b][j][k]+calc(k,cvt(S[i])));
            }
    for(int i=0;i<16;++i)
        for(int j=0;j<16;++j)
            ans=std::max(ans,dp[N&1][i][j]);
    printf("%d\n",ans);
}
