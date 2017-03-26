#include <stdio.h>

int T, c;
unsigned long long N;
int main() {
    for(scanf("%d", &T);T;T--) {
        scanf("%llu", &N);
        c = 0;
        while(N) {
            if(N & 1)
                if(N & 2 && N ^ 3)
                    N++;
                else
                    N--;
            else
                N >>= 1;
            c++;
        }
        printf("%d\n", c);
    }
}
