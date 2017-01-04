#include <stdio.h>

int N;
double a, b;
int main() {
    scanf("%d%lf%lf", &N, &a, &b);
    printf("%.6f", -1*b/(a*N));
}
