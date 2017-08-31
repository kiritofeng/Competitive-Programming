#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+4, RT=320, INF=0x3f3f3f3f;
int N, Q, A[MAXN], BK[RT];
int main() {
    scanf("%d", &N);
    for(int i=0;i<N;scanf("%d", A+i++));
    memset(BK, 0x3f, sizeof BK);
    for(int i=0;i<N;++i)
        BK[i/RT]=min(BK[i/RT], A[i]);
    scanf("%d", &Q);
    for(int i=0,l,r,res;i<Q;++i) {
        scanf("%d%d", &l, &r);
        res=INF;
        while(l%RT&&l<=r)
            res=min(res,A[l++]);
        while(l+RT<=r) {
            res=min(res,BK[l/RT]);
            l+=RT;
        }
        while(l<=r)
            res=min(res,A[l++]);
        printf("%d\n", res);
    }
}
