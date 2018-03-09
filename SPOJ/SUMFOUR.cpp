#include<bits/stdc++.h>
typedef long long ll;
const int MN=2504;
int N,A[MN],B[MN],C[MN],D[MN];
std::unordered_map<int,int>cnt;
ll ans;
int main(){
    scanf("%d",&N);
    for(int i=0;i<N;++i)
        scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
    cnt.reserve(MN*MN);
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j)
            ++cnt[A[i]+B[j]];
    for(int i=0;i<N;++i)
        for(int j=0;j<N;++j){
            auto it=cnt.find(-(C[i]+D[j]));
            if(it!=cnt.end()) ans+=it->second;
        }
    printf("%lld\n",ans);
}
