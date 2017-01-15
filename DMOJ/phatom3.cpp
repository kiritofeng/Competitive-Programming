#include <bits/stdc++.h>

using namespace std;

long long N, M, counter;
bitset<2000004> root;
bitset<20000004>ans;

int main() {
    scanf("%lld%lld", &N, &M);
    root.set();
    ans.set();
    for(long long i=4;i*i*i*i<M;i+=2)
        root[i]=false;
    for(long long i=3;i*i*i*i<M;i+=2)
        if(root[i])
            for(long long j=i*i;j*j<M;j+=i)
                root[j]=false;
    for(long long i=N>=2?N%2:N%2+2;i+N<M;i+=2)
        ans[i]=false;
    for(long long i=3;i*i<M;i+=2)
        if(root[i])
            for(long long j=N>i?(i-N%i)%i:i*i-N;j<M-N+2;j+=i)
                ans[j]=false;
    for(long long i=N;i<M;i++)
        if(ans[i-N]) counter++;
    printf("%lld\n", counter);
    return 0;
}
