#include<bits/stdc++.h>
#define INC(A,B) A = ((A) + (B)) % MOD
typedef long long ll;
typedef long long ll;
const int MN = 104, ML = 1004, MOD = 1e9+7, inf = 0x3f3f3f3f;
int N,L,A[MN];
// dp[currently adding][cc count][total][endpoints]
ll ans,dp[MN][MN][ML][3];
int main() {
    scanf("%d%d",&N,&L);
    for(int i=0;i<N;++i)
        scanf("%d",&A[i]);
    std::sort(A,A+N);
    if(N == 1) {
        puts("1");
        return 0;
    }
    // set this to a small infinity
    // i.e. so that diff*2*j does not overflow int
    A[N] = ML;
    // handle A[0]
    if(A[1]-A[0] <= L) dp[1][1][A[1]-A[0]][1] = 2; // endpoints are legal
    if(2*(A[1]-A[0]) <= L) dp[1][1][2*(A[1]-A[0])][0] = 1; // middle is legal
    for(int i=1;i<N;++i) {
        int diff = A[i+1] - A[i];
        for(int j=0;j<=i;++j) {
            for(int k=0;k<=L;++k) {
                for(int l=0;l<3;++l) {
                    if(!dp[i][j][k][l]) continue; // value DNE
                    // fill endpoints
                    if(l < 2 && k+diff*(2*j-l-1) <= L) {
                        // there are 2*j-l-1 positions to upgrade
                        // -1 because one of positions is merged with endpoints
                        if(i == N-1) {
                            // because diff is infinity, 2*j-l-1 = 0
                            // thus this case is just placing A[N-1] at endpoint
                            // have j ccs to potentially merge with
                            INC(dp[i+1][j][k+diff*(2*j-l-1)][l+1],dp[i][j][k][l]*j);
                        } else if(!l || j > 1) { // ensure this case will never coincide with i = N - 1
                            // can merge with any cc but endpoints
                            // remember that cc positions are not fixed
                            INC(dp[i+1][j][k+diff*(2*j-l-1)][l+1],dp[i][j][k][l]*(2-l)*(j-l));
                        }
                        if(k+diff*(2*j-l+1) <= L) { // create new cc
                            // can create either endpoint
                            INC(dp[i+1][j+1][k+diff*(2*j-l+1)][l+1], dp[i][j][k][l]*(2-l));
                        }
                    }
                    // consider cases that don't fill ends
                    // case 1: create new cc
                    if(k+diff*(2*j-l+2) <= L) { // two new positions to upgrade
                        INC(dp[i+1][j+1][k+diff*(2*j-l+2)][l],dp[i][j][k][l]);
                    }
                    // case 2: stick to preexisting CC
                    if(k+diff*(2*j-l) <= L) { // no new positions to upgrade
                        // there are 2*j-l positions for new element
                        INC(dp[i+1][j][k+diff*(2*j-l)][l], dp[i][j][k][l]*(2*j-l));
                    }
                    // case 3: merge two cc
                    if((k+diff*(2*j-l-2)<=L) && (j>=2) && (i==N-1 || j>2 || l<2)) {
                        // the first condition is obvious
                        // the second condition is also obvious
                        // if j = 2, and l = 2, you are stuck with exactly prefix and suffix
                        // merging is possible iff i = N - 1
                        // if i < N - 1 and l = 2, the prefix and suffix are built already
                        // but you cannot merge them (i < N - 1)
                        // therefore you must merge with another component
                        // if i < N - 1 and j = 2, you can merge iff they are not exactly prefix and suffix
                        if(!l) {
                            // no endpoints, so you can merge any of the j
                            // order matters, so there are jP2 possible merges
                            INC(dp[i+1][j-1][k+diff*(2*j-l-2)][l],dp[i][j][k][l]*j*(j-1));
                        } else if(l == 1) {
                            // one endpoints, so you can either merge the (j-1) non-endpoints
                            // either with themselves, or the endpoint
                            // there are (j-1)P2 ways to merge non-endpoints
                            // and (j-1) ways to merge endpoint
                            // note that (j-1)P2 + (j-1) = (j-1)*(j-2) + (j-1) = (j-1)*(j-1)
                            INC(dp[i+1][j-1][k+diff*(2*j-l-2)][l],dp[i][j][k][l]*(j-1)*(j-1));
                        } else { // both endpoints exist
                            if(i == N-1) { // merge prefix and suffix, exactly 1 position for A[N-1]
                                INC(dp[i+1][j-1][k+diff*(2*j-l-2)][l],dp[i][j][k][l]);
                            } else {
                                // two endpoints, and i < N - 1, so you can either merge the (j-2) non-endpoints
                                // either with themselves, or the endpoint
                                // there are (j-2)P2 ways to merge non-endpoints
                                // and 2*(j-2) ways to merge with an endpoint
                                // note that (j-2)P2 + 2*(j-2) = (j-2)*(j-3) + 2*(j-2) = (j-2)*(j-1)
                                INC(dp[i+1][j-1][k+diff*(2*j-l-2)][l],dp[i][j][k][l]*(j-1)*(j-2));
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<=L;++i) {
        // we want N because that is after everyone has been added
        // we want 1 cc (everyone)
        // we want both endpoints
        INC(ans,dp[N][1][i][2]);
    }
    printf("%lld\n", ans);
}
