#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 5004, seed = 10007;
int len;
char c[MAXN];
bitset<MAXN>vis;
unordered_set<ll>us;
ll h[MAXN], p[MAXN];

ll compute_hash(int i, int j) {
    return h[j] - h[i - 1] * p[j - i + 1];
}

void check(int ln) {
    for(int i=1, j;i<=len;i++) {
        if(!vis.test(i)) {
            vis.set(i);
            j = 1;
            while(i + j * ln + ln - 1 <= len && compute_hash(i, i + ln - 1) == compute_hash(i + j * ln, i + j * ln + ln - 1)) {
                vis.set(i + j * ln);
                us.insert(compute_hash(i, i + j * ln + ln - 1));
                j++;
            }
        }
    }
}

int main() {
    scanf("%s", c);
    len = strlen(c);
    p[0] = h[0] = 1;
    for(int i=1;i<=len;i++) {
        h[i] = h[i - 1] * seed + c[i - 1];
        p[i] = p[i - 1] * seed;
    }
    for(int i=1;i<=len;i++) {
        vis.reset();
        check(i);
    }
    printf("%lu", us.size());
}
