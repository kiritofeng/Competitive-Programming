#include<bits/stdc++.h>
const int MN=3e4+4,RT=250;
int N,D,cnt[MN],memo[MN][2*RT];
// dp state is [cur], jump - [diff]
template<typename T>
inline T max(T t){
    return t;
}
template<typename T,typename... A>
inline T max(T t,A... a){
    T ret=max(a...);
    return ret>t?ret:t;
}
int dp(int src,int diff){
    if(src>=MN||diff<0) return 0;
    int &res=memo[src][diff];
    if(~res) return res;
    int delta=diff-RT;
    if(delta+D<=0) return 0;
    res=max(dp(src+delta+D,diff),dp(src+delta+D-1,diff-1),dp(src+delta+D+1,diff+1))+cnt[src];
    return res;
}
int main(){
    scanf("%d%d",&N,&D);
    for(int i=1,a;i<=N;++i){
        scanf("%d",&a);
        ++cnt[a];
    }
    memset(memo,-1,sizeof memo);
    printf("%d\n",dp(D,RT));
}
