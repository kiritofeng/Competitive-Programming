#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()

using namespace std;

const int MAXLEN = 100004, seed = 31, mod = 1000000009;
int N, M, h, len, ans;
char S[MAXLEN];
unordered_map<int, vector<int>>pre, wrd;
int main() {
    scanf("%d%d", &N, &M);
    for(int i=1;i<=N;i++) {
        scanf("%s", &S);
        len = strlen(S);
        h = 0;
        for(int j=0;j<len;j++) {
            h = (h * seed + S[j] - 'a' + 1) % mod;
            pre[h].push_back(i);
        }
        wrd[h].push_back(i);
    }
    for(int i=0, a, b;i<M;i++) {
        h = 0;
        ans = 0;
        scanf("%s%d%d", &S, &a, &b);
        len = strlen(S);
        for(int j=0;j<len - 1;j++) {
            h = (h * seed + S[j] - 'a' + 1) % mod;
            ans += upper_bound(all(wrd[h]), b) - lower_bound(all(wrd[h]), a);
        }
        h = (h * seed + S[len - 1] - 'a' + 1) % mod;
        ans += upper_bound(all(pre[h]), b) - lower_bound(all(pre[h]), a);
        printf("%d\n", ans);
    }
}
