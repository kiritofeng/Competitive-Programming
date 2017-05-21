#include <bits/stdc++.h>

using namespace std;

const int MAXN=200004, RT=420;
int N, Q, A[MAXN], B[MAXN][2];
int main() {
    scanf("%d", &N);
    for(int i=0;i<N;i++)
        scanf("%d", A + i);
    for(int i=0;i<MAXN;i++) {
        B[i][1] = N;
    }
    for(int i=N-1;i>=0;i--)
        if((i + A[i])/RT > i/RT) {
            B[i][0] = 1;
            B[i][1] = i + A[i];
        } else {
            B[i][0] = B[i + A[i]][0] + 1;
            B[i][1] = B[i + A[i]][1];
        }
    scanf("%d", &Q);
    for(int i=0, a, b, c, ans=0, tmp;i<Q;i++) {
        scanf("%d", &a);
        switch(a){
            case 1:
                scanf("%d", &b);
                ans=0;
                while(b < N) {
                    ans += B[b][0];
                    b = B[b][1];
                }
                printf("%d\n", ans);
                break;
            case 2:
                scanf("%d%d", &b, &c);
                tmp = b/RT;
                A[b]=c;
                for(;b/RT==tmp && b >= 0;b--)
                    if((b + A[b])/RT > b/RT) {
                        B[b][0] = 1;
                        B[b][1] = b + A[b];
                    } else {
                        B[b][0] = B[b + A[b]][0] + 1;
                        B[b][1] = B[b + A[b]][1];
                    }
                    break;
                }
    }
}
