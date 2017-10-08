#pragma GCC optimize("Ofast")
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<unordered_map>
#include<vector>
using namespace std;
typedef long long ll;
const int MAXN=262200,RT1=100,RT2=MAXN/RT1,mod=1<<18;
int N,Q,A[MAXN],ans;
vector<int>ap[MAXN];
ll M[MAXN],sol[RT2][RT2];
#define all(x) x.begin(),x.end()
inline int bf(int i, int l, int r) {
    return upper_bound(all(ap[i]),r)-lower_bound(all(ap[i]),l);
}
int main() {
    scanf("%d%d",&N,&Q);
    for(int i=0;i<N;++i) {
        scanf("%d",A+i);
        ap[A[i]].emplace_back(i);
    }
    for(int i=0;i<RT2;++i) {
        memset(M, 0, sizeof M);
        ll tmp = 0;
        for(int j=i*RT1;j<N;++j) {
            tmp=(tmp+2*++M[A[j]]-1)%mod;
            sol[i][j/RT1]=tmp;
        }
    }
    for(int i=0,l,r,lb,rb;i<Q;++i) {
        scanf("%d%d",&l,&r);
        l^=ans;
        r^=ans;
        lb=l/RT1+1;
        rb=r/RT1;
        ans = 0;
        if(lb<rb) {
            ans = sol[lb][rb-1];
            for(int j=RT1*lb-1,tmp;j>=l;--j) {
                tmp=bf(A[j],j,rb*RT1-1);
                ans=((ans+2LL*tmp-1)%mod+mod)%mod;
            }
            for(int j=rb*RT1,tmp;j<=r;++j) {
                tmp=bf(A[j],l,j);
                ans=((ans+2LL*tmp-1)%mod+mod)%mod;
            }
            //Watch for last block
        } else {
            for(int j=l,tmp;j<=r;++j) {
                tmp=bf(A[j],l,j);
                ans=((ans+2*tmp-1)%mod+mod)%mod;
            }
        }
        printf("%d\n",ans);
    }
}
