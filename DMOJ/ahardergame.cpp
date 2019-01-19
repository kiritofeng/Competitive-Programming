#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6+4;
int N, s1, s2, A[MAXN];
vector<int>V;

int main() {
    scanf("%d", &N);
    for(int i=0;i<N;++i)
        scanf("%d", A + i), s1 += A[i];
    for(int i=0, tmp;i<N;++i) {
        V.emplace_back(A[i]);
        while(V.size() > 2 && V[V.size() - 3] <= V[V.size() - 2] && V[V.size() - 2] >= V[V.size()-1]) {
            tmp = V[V.size() - 3] - V[V.size() - 2] + V[V.size() - 1];
            V.pop_back(), V.pop_back(), V.pop_back();
            V.push_back(tmp);
        }
    }
    sort(V.begin(), V.end(), greater<int>());
    for(int i=0, s=1;i<V.size();++i)
        s2 += s * V[i], s *= -1;
    printf("%d", s1+s2>>1);
}
