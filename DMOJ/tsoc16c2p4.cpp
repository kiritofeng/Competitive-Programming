#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10004, MAXM = 104;
int N, M, cost[MAXM];
vector<int>primes;
bitset<MAXN>sieve, vis, dp[MAXM];

int main() {
    //Get primes
    sieve.set();
    sieve[0] = sieve[1] = 0;
    for(int i=4;i<MAXM;i+=2)
        sieve.reset(i);
    primes.emplace_back(2);
    for(int i=3;i*i<=MAXN;i+=2)
        if(sieve.test(i))
            for(int j=i*i;j<MAXN;j+=i)
                sieve.reset(j);
    //Push into vector
    for(int i=3;i<MAXN;i+=2)
        if(sieve[i])
            primes.emplace_back(i);
    scanf("%d%d", &N, &M);
    for(int i=1;i<=M;i++)
        scanf("%d", cost + i);
    dp[0][0] = 1;
    for(int i=1;i<=M;i++)
        for(int p:primes)
            for(int j=p*cost[i];j<MAXN;j++)
                if(dp[i-1][j-p*cost[i]])
                    dp[i].set(j);
    for(int p:primes) {
        if(p > N) break;
        if(dp[M][p])
            return puts("its primetime"), 0;
    }
    puts("not primetime");
}
