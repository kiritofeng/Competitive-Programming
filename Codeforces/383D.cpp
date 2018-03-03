#include<bits/stdc++.h>
const int MN=1e3+4,MS=1e4+4,MOD=1e9+7;
int N,ans,A[MN],dp[MN][MS*2];
int main(){
    scanf("%d",&N);
    for(int i=1;i<=N;++i){
        scanf("%d",A+i);
        for(int j=A[i];j<MS*2;++j){
            if(dp[i-1][j]){
                dp[i][j-A[i]]=(dp[i][j-A[i]]+dp[i-1][j])%MOD;
            }
            if(dp[i-1][j-A[i]]){
                dp[i][j]=(dp[i][j]+dp[i-1][j-A[i]])%MOD;
            }
        }
        dp[i][MS+A[i]]=(dp[i][MS+A[i]]+1)%MOD;
        dp[i][MS-A[i]]=(dp[i][MS-A[i]]+1)%MOD;
        ans=(ans+dp[i][MS])%MOD;
    }
    printf("%d",ans);
}
