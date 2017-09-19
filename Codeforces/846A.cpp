#include<bits/stdc++.h>
using namespace std;
const int MAXN=104;
int N, ans, A[MAXN];
int main() {
    scanf("%d",&N);
    for(int i=1;i<=N;scanf("%d",A+i++));
    A[0]=1;
    for(int i=0,a=0,b=0;i<=N;++i) {
        a+=!A[i];
        b=0;
        //Assume all after i are 1
        for(int j=i+1;j<=N;++j)
            b+=A[j];
        ans=max(ans,a+b);
    }
    printf("%d",ans);
}
