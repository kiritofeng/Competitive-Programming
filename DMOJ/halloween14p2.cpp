#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
const int MAXN = 500004;
vector<pll>neko;
int N;
ll W, dp[MAXN];
pll last;
#define all(x) x.begin(), x.end()

int main() {
    scanf("%d %lld", &N, &W);
    neko.push_back({0, 0});
    dp[0] = 0;
    char c;
    for(int i=0, j=0, a, b;i<N;i++) {
        scanf(" %c", &c);
        switch(c) {
            case 'A':
                scanf("%d %d", &a, &b);
                last = neko.back();
                neko.push_back({a + last.first, b + last.second});
                dp[j + 1] = max(dp[j], neko.back().second - lower_bound(all(neko), make_pair(neko.back().first - W, 0LL)) -> second);
                printf("%lld\n", dp[++j]);
                break;
            case 'D':
                neko.pop_back();
                j--;
                break;
        }
    }
}
