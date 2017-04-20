#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll seed = 1029;
const ll mod = 10000009;
int ans;
ll h1, h2, b, hashes[1000004];
string s1, s2;

//I would like to thank r3mark for teaching me about hashes

inline ll m(ll l) {
    while(l<0) l += mod;
    while(l > mod) l -= mod;
    return l;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> s1 >> s2;
    for(int i=0;i<s2.length();i++) {
        h2 = m(((h2 % mod) * (seed % mod) % mod) + (s2[i] - 'A' + 1) % mod);
        if(s2[i] == s1[s1.length() -1])hashes[i]=h2;
    }
    ans = s1.length();
    b = 1;
    for(int i = s1.length() - 1; i >=0; i --) {
        h1 = m((((s1[i] - 'A' + 1) % mod) * b % mod) + h1);
        b = (b * seed) % mod;
        if(hashes[s1.length() - 1 - i] && hashes[s1.length() - 1 - i] == h1) {
            ans = i;
        }
    }
    cout << s1.substr(0, ans) << s2;
}
