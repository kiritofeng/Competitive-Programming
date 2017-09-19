#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=5004;
const ll LINF=0x3f3f3f3f3f3f3f3f;
int N,i1,i2,i3,A[MAXN];
ll ans=-LINF,psa[MAXN];
int main() {
    scanf("%d",&N);
    for(int i=1;i<=N;scanf("%d",A+i++));
    for(int i=1;i<=N;++i)
        psa[i]=psa[i-1]+A[i];
    for(int i=1,st,ed;i<=N;++i) {
        //This is cut point 1
        ll subsum=0,bestsubsum=0;
        st=i,ed=i;
        for(int j=i,sst=i;j<=N;++j) {
            if(subsum<0)
                sst=j;
            subsum=max(subsum,0LL)+A[j];
            if(subsum>bestsubsum) {
                st=sst;
                ed=j+1;
                bestsubsum=subsum;
            }
        }
        if(-psa[N]+2*psa[i-1]+2*bestsubsum>ans) {
            i1=i;
            i2=st;
            i3=ed;
            ans=-psa[N]+2*psa[i-1]+2*bestsubsum;
        }
    }
    printf("%d %d %d",i1-1,i2-1,i3-1);
}
