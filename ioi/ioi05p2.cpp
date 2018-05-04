#include<bits/stdc++.h>
typedef long long ll;
int N,prev=-1e9;
std::pair<ll,ll>ans;
int main(){
    scanf("%d",&N);
    ans={-1e9,1e9};
    for(int i=0,a;i<N;++i){
        scanf("%d",&a);
        ans.second=std::min(ans.second,1LL*a);
        ans.first=2LL*a-ans.first;
        ans.second=2LL*a-ans.second;
        std::swap(ans.first,ans.second);
    }
    if(a.first>a.second) puts("0");
    else printf("%lld\n",ans.second-ans.first+1);
}
