#include <bits/stdc++.h>

#define a(x) (x) & 1 ^ 1

using namespace std;

int N, dp[2][5004];
string S, rS;
int main() {
    cin >> N;
    cin >> S;
    rS = S;
    reverse(rS.begin(), rS.end());
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=N;j++) {
            if(S[i - 1]==rS[j - 1])
                dp[a(i)][j] = dp[a(i ^ 1)][j - 1] + 1;
            else
                dp[a(i)][j] = max(dp[a(i ^ 1)][j], dp[a(i)][j - 1]);
        }
    }
    printf("%d", S.length() - dp[a(N)][N]);
}
