#include <bits/stdc++.h>
#include <bits/extc++.h>

#define all(x) x.begin(), x.end()

using namespace std;

typedef pair<int, int> pii;

struct edge {
    int src, des, w, o;

    bool operator <(const edge &e) const {
        return w < e.w || (w == e.w && o < e.o);
    }
};

const int MAXN = 100004, MAXM = 200004;
int N, M, D, ee, weight, days, ds[MAXN];
vector<edge>edges;

void init() {
    for(int i=1;i<=N;i++) ds[i] = i;
}

int find(int x) {
    return ds[x] = (x == ds[x] ? x: find(ds[x]));
}

bool connected(int x, int y) {
    return find(x) == find(y);
}

bool merge(int x, int y) {
    int xr = find(x), yr = find(y);
    if(xr ^ yr)
        return ds[xr] = yr;
    return 0;
}

int main() {
    scanf("%d%d%d", &N, &M, &D);
    for(int i=1, a, b, c;i<=M;i++) {
        scanf("%d%d%d", &a, &b, &c);
        if(i < N)
            edges.push_back({a, b, c, 0});
        else
            edges.push_back({a, b, c, 1});
    }
    sort(all(edges));
    init();
    int i, maxe=0;
    for(i=0;i<edges.size();i++) {
        if(ee == N - 1) break;
        auto e = edges[i];
        if(merge(e.src, e.des)) {
            ee++;
            maxe = e.w;
            if(e.o)
                days ++;
        }
    }
    //Either days, or days - 1 is the answer
    //Want to replace a new edge with an old edge with same or lesser cost
    if(edges[i-1].o) {
        init();
        for(int i=0;i<edges.size();i++) {
            auto e = edges[i];
            if(!connected(e.src, e.des))
                if(e.w < maxe || (e.w == maxe && !e.o))
                    merge(e.src, e.des);
                else if(!e.o && e.w <= D) {
                    printf("%d", days - 1);
                    return 0;
                }
        }
    }
    printf("%d", days);
}
