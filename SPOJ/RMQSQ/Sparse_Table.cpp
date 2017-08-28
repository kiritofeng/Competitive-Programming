#include <bits/stdc++.h>

using namespace std;

const int MAXN=100004, MAXLN=18, INF=0x3f3f3f3f;
int N, Q, st[MAXN][MAXLN];
int query(int l, int r) {
    int ans = 0x3f3f3f3f;
    for(int i=MAXLN;i>=0;--i)
        if(l+(1<<i)-1<=r) {
            ans = min(ans, st[l][i]);
            l+=1<<i;
        }
    return ans;
}
int main() {
    scanf("%d", &N);
    for(int i=0;i<N;++i)
        scanf("%d", &st[i][0]);
    for(int j=1;j<MAXLN;++j)
        for(int i=0;i+(1<<j-1)<N;++i)
            st[i][j] = min(st[i][j-1], st[i+(1<<j-1)][j-1]);
    scanf("%d", &Q);
    for(int i=0, l, r;i<Q;++i) {
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r));
    }
}
