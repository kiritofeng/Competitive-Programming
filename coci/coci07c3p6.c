#include <stdio.h>

#define MAXN 250004
#define RT 504
int N, M, blk[RT][10], sft[RT];
char S[MAXN];
int main() {
    scanf("%d%d", &N, &M);
    scanf("%s", S);
    for(int i=0;i<N;i++)
        ++blk[i/RT][S[i]-'0'];
    for(int i=0, a, b, ans;i<M;i++) {
        scanf("%d%d", &a, &b);
        ans = 0;
        --a, --b;
        while(a % RT && a <= b) {
            ans += (S[a] - '0' + sft[a/RT]) % 10;
            --blk[a/RT][S[a] - '0'];
            S[a] = (S[a] - '0' + 1) % 10 + '0';
            ++blk[a/RT][S[a] - '0'];
            ++a;
        }
        while(a + RT < b) {
            for(int j=0;j<10;j++)
                ans += ((j + sft[a/RT]) % 10) * blk[a/RT][j];
            ++sft[a/RT];
            a += RT;
        }
        while(a <= b) {
            ans += (S[a] - '0' + sft[a/RT]) % 10;
            --blk[a/RT][S[a] - '0'];
            S[a] = (S[a] - '0' + 1) % 10 + '0';
            ++blk[a/RT][S[a] - '0'];
            ++a;
        }
        printf("%d\n", ans);
    }
    return 0;
}
