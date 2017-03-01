#include <bits/stdc++.h>

using namespace std;

int N, M, cache[44];
string A[40], B[40];

bool is_prefix(string s1, int i1, string s2, int i2) {
    for(int i=min(i1, i2);i<min(s1.length(), s2.length());i++)
        if(s1[i] != s2[i]) return 0;
    return 1;
}

bool dp(string sa, string sb, int k) {
    if(!sa.empty() && !sb.empty() && sa == sb) return 1;
    if(!k) return 0;
    for(int i=1;i<=N;i++) {
        string t1 = sa + A[i], t2 = sb + B[i];
        if(is_prefix(t1, sa.length(), t2, sb.length()) && dp(t1, t2, k - 1)) {
            cache[k] = i;
            return 1;
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> M;
    cin >> N;
    for(int i=1;i<=N;i++)
        cin >> A[i];
    for(int i=1;i<=N;i++)
        cin >> B[i];
    if(dp("", "", M)) {
        int cnt = M, ans=0;
        while(cache[cnt--]) ans++;
        cout << ans << "\n";
        cnt = M;
        while(cache[cnt]) {
            cout << cache[cnt] << "\n";
            cnt--;
        }
    } else {
        cout << "No solution.";
    }
}
