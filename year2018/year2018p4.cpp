#include<bits/stdc++.h>
typedef long long ll;
const int MSUM=162,MDIG=20;
int ans,digit[MDIG];
ll L,R,memo[MDIG][MSUM+1];
ll dp(int pos,int s,bool limit){
    if(s<0) return 0;
    if(!pos) return !s;
    if(!limit&&~memo[pos][s]) return memo[pos][s];
    ll tmp=0;
    int up=limit?digit[pos]:9;
    for(int i=0;i<=up;++i)
        tmp+=dp(pos-1,s-i,limit&&(i==digit[pos]));
    if(!limit) return memo[pos][s]=tmp;
    else return tmp;
}
ll solve(ll l,int s){
    int i=0;
    memset(digit,0,sizeof digit);
    while(l) digit[++i]=l%10,l/=10;
    return dp(i,s,1);
}
int main(){
    memset(memo,-1,sizeof memo);
    scanf("%lld%lld",&L,&R);
    for(int i=1;i<=MSUM;++i)
        ans+=solve(R,i)>solve(L-1,i);
    printf("%d\n",ans);
}
