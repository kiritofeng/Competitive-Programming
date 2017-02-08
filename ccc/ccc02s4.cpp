#include <bits/stdc++.h>

using namespace std;

typedef pair<int, bitset<104>> pleb;

int M, Q, s[104];
pleb memo[104];
string names[104];

pleb dp(int a) {
    if(a > Q) return {0, bitset<104>()};
    if(memo[a].first != -1) return memo[a];
    bitset<104> btmp;
    int tmp=s[a], ans = 0x3f3f3f;
    for(int i=0;i<M && a + i <= Q;i++) {
        tmp = max(tmp, s[a + i]);
        pleb ptmp = dp(a + i + 1);
        if(tmp + ptmp.first < ans) {
           ans = tmp + ptmp.first;
           btmp = ptmp.second;
        }
    }
    btmp.set(a);
    return memo[a] = {ans, btmp};
}

int main() {
    cin >> M >> Q;
    for(int i=1;i<=Q;i++) {
        cin >> names[i] >> s[i];
        memo[i].first = -1;
    }
    pleb p = dp(1);
    cout << "Total Time: " << p.first;
    for(int i=1;i<=Q;i++) {
        if(p.second[i]) cout << "\n";
        cout << names[i] << " ";
    }
}
