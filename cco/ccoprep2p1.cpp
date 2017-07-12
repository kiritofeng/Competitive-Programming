#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, M, T, last, A[4] = {0, 1, 1, 0}, V[10];

struct matrix {
    ll mat[3][3];

    matrix(){
        memset(mat, 0, sizeof mat);
    }

    ll* operator [] (int i) {
        return mat[i];
    }

    matrix operator * (matrix m) {
        matrix res = matrix();
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                    res[i][j] = (res[i][j] + ((mat[i][k] % M) * (m[k][j]) % M) % M) % M;
        return res;
    }

    void operator * (ll * AA) {
        ll ret[4] = {0};
        for(int i=0;i<3;i++)
            for(int k=0;k<3;k++)
                ret[i] = (ret[i] + ((mat[i][k] % M) * (AA[k] % M)) % M) % M;
        for(int i=0;i<3;i++)
            AA[i] = ret[i];
    }

    void print() {
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++)
                printf("%lld\t", mat[i][j]);
            printf("\n");
        }
    }

} mat, id, tmp;

matrix exp(matrix m, ll p) {
    if(!p) return id;
    if(!(p^1)) return m;
    if(p&1) return m*exp(m*m, p>>1);
    return exp(m*m, p >> 1);
}

void nxt_mat() {
    last = A[0];
    A[0] = ((last * ((T * 10) % M)) % M + T % M) % M;
    A[1] = ((A[0] * ((T * 10) % M)) % M + (T + 1) % M) % M;
    A[2] = 1;
    T *= 10;
    mat[1][0] = ((-T % M) + M) % M;
    mat[1][1] = (T + 1) % M;
}

int main() {
    scanf("%lld%lld", &N, &M);
    for(int i=0;i<3;i++)
        id[i][i] = 1;
    mat[0][1] = 1;
    mat[1][2] = 1;
    mat[2][2] = 1;
    T = 1;
    while(T * 10 < N) {
        nxt_mat();
        tmp = exp(mat, T - 1 - T/10);
        tmp * A;
    }
    nxt_mat();
    if(N == T) {
        exp(mat, N - T/10 - 1) * A;
        nxt_mat();
    } else
        exp(mat, N - T/10) * A;
    printf("%lld", (A[0] % M + M) % M);
}
