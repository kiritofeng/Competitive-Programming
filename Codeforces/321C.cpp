#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100004;
int N, sz[MAXN], cen[MAXN];
vector<int>adj[MAXN];

int subsize(int src, int par) {
    sz[src] = 1;
    for(int i: adj[src])
        if(i ^ par)
            sz[src] += subsize(i, src);
    return sz[src];
}

void centroid(int src, int s, int depth = 1) {
    if(cen[src]) return;
    for(int i:adj[src])
        if(sz[i] > s/2) {
            int temp = 1;
            for(int j:adj[src])
                if(!cen[j] && j != i) temp += sz[j];
            sz[src] = temp;
            centroid(i, s, depth);
            return;
        }
    //This is a centroid
    cen[src] = depth;
    sz[src] = 0;
    for(int i:adj[src])
        centroid(i, sz[i], depth + 1);
}

int main() {
    scanf("%d", &N);
    for(int i=1, a, b;i<N;i++) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    subsize(1, -1);
    centroid(1, N);
    for(int i=1;i<=N;i++)
        printf("%c ", cen[i] + 'A' - 1);
}
