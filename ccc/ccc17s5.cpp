#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150004, R = 400;

int N, M, Q, ind[MAXN], L[MAXN], A[MAXN], C[MAXN], SQRT[MAXN/R];
vector<int>V[MAXN];
int RHT[MAXN][410];

int pmod(int a, int b) {
    return (a % b + b) % b;
}

int val(int i) {
    int t = L[i], s = V[t].size();
    assert(s);
    int p = pmod(ind[i] - C[t], s);
    //printf("p: %d\n", p);
    return A[V[t][p]];
}

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    memset(RHT, -1, sizeof RHT);
    for(int i=1;i<=N;i++) {
        scanf("%d", &L[i]);
        V[L[i]].push_back(i);
        ind[i] = V[L[i]].size() - 1;
        RHT[L[i]][i/R] = i;
    }
    for(int i=1;i<=N;i++) {
        scanf("%d", &A[i]);
        SQRT[i/R] += A[i];
    }
    for(int i=0, a, b, c;i<Q;i++) {
        //printf("Q: %d\n", i);
        scanf("%d", &a);
        if(a ^ 2) {
            scanf("%d%d", &b, &c);
            int ans = 0;
            if(c - b < R)
                for(int j=b;j<=c;j++) {
                    //printf(">>>%d %d\n", j, val(j));
                    ans += val(j);
                }
            else {
                while(b%R) {
                    ans += val(b);
                    b++;
                }
                while(b + R <= c) {
                    //printf("SQRT IND: %d\n", b/R);
                    ans += SQRT[b/R];
                    b += R;
                }
                while(b <= c) {
                    //printf("FLT: %d\n", b);
                    ans += val(b);
                    b++;
                }
            }
            printf("%d\n", ans);
        } else {
            scanf("%d", &b);
            int beginning = -1, prev = 0;
            for (int i = 0; i < R; i++){
                int rt = RHT[b][i];
                if (rt==-1) continue;
                if(beginning==-1) beginning = i;
                SQRT[i]+=prev;
                prev = val(rt);
                SQRT[i]-=prev;
            }
            SQRT[beginning] += prev;
            C[b] = (C[b] + 1) % V[b].size();
        }
    }
}
