#include <bits/stdc++.h>

using namespace std;

template<typename T>
void operator +=(vector<T> &v, T t) {
    v.push_back(t);
}

const int MAXD = 1004;
int D, F, T, W[MAXD], B[MAXD], BB[MAXD];
vector<int>adj[MAXD];
int main() {
    scanf("%d", &D);
    for(int i=1;i<=D;i++)
        scanf("%d", &W[i]);
    scanf("%d", &F);
    for(int i=0, a, b;i<F;i++) {
        scanf("%d%d", &a, &b);
        adj[a] += b;
    }
    scanf("%d", &T);
    memset(BB, -1, sizeof BB);
    BB[1] = 0;
    for(int i=0;i<=T;i++)
        for(int j=1;j<=D;j++)
            if(BB[j]==i) {
                for(int k:adj[j])
                    if(BB[k] < i)
                        BB[k] = i + W[k];
                B[j]++;
            }
    for(int i=1;i<=D;i++)
        printf("%d\n", B[i]);
}
