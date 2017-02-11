#include <stdio.h>

typedef long long ll;

#define MOD 1000000007LL

int N;
bool cnt;
ll ans = 1, matrix[504][504];

inline ll abs(const ll &a) {
    return a<0?-a:a;
}

inline ll modinv(const ll &a, const ll &b, const ll &c = MOD) {
    if(!b) return 1;
    if(!(b^1)) return a % c;
    if(b&1) return (a % c) * modinv((a % c) * (a % c) % c, b >> 1, c) % c;
    return modinv((a % c) * (a % c) % c, b >> 1, c) % c;
}

inline ll mod(const ll &a, const ll &b = MOD) {
    return (a % b + b) % b;
}

int main() {
    scanf("%d", &N);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            scanf("%lld", &matrix[i][j]);
    for(int i=0;i<N-1;i++) {
        int max_ind=i;
        while(max_ind < N && matrix[max_ind][i] == 0) max_ind++;
        if(max_ind == N) {
            printf("0");
            return 0;
        }
        if(max_ind != i) {
            for(int j=i;j<N;j++) {
                ll tmp = matrix[i][j];
                matrix[i][j] = matrix[max_ind][j];
                matrix[max_ind][j] = tmp;
            }
            cnt ^= 1;
        }
        for(int j=i + 1;j < N;j++) {
            ll m = matrix[j][i], inv = modinv(matrix[i][i], MOD - 2);
            for(int k = i;k<N;k++)
                matrix[j][k] = mod(matrix[j][k] - mod(mod(matrix[i][k] * inv) * m));
        }
    }
    for(int i=0;i<N;i++)
        ans = mod(ans * matrix[i][i]);
    if(cnt) printf("%lld", mod(-ans, MOD));
    else printf("%lld", mod(ans, MOD));
}
