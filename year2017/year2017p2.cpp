#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;

struct block {
    int x, y;
    bool z;

    block(int a, int b, int c) {
        x = a;
        y = b;
        z = c;
    }

    bool operator <(const block &b) const {
        return make_pair(x, y) < make_pair(b.x, b.y);
    }
};

bool cmpy(const block &a, const block &b) {
    return make_pair(a.y, a.x) < make_pair(b.y, b.x);
}

unsigned long long convert(const block &b) {
    return 10000000000LL * b.x + b.y;
}

int N, M, X, Y, O, E;
vector<block>cdx, cdy;
unordered_map<unsigned long long, int>vis;
queue<block>Q;
int main() {
    scanf("%d%d", &N, &M);
    scanf("%d%d", &X, &Y);
    scanf("%d", &O);
    for(int i=0, x, y;i<O;i++) {
        scanf("%d%d", &x, &y);
        cdx.push_back({x, y, 0});
        cdy.push_back({x, y, 0});
    }
    scanf("%d", &E);
    for(int i=0, x, y;i<E;i++) {
        scanf("%d%d", &x, &y);
        cdx.push_back({x, y, 1});
        cdy.push_back({x, y, 1});
    }
    sort(all(cdx));
    sort(all(cdy), cmpy);
    Q.push({X, Y, 0});
    vis[convert(Q.front())] = 0;
    while(!Q.empty()) {
        block cur = Q.front();
        Q.pop();
        long long l = convert(cur);
        if(cur.z) {
            //Exit
            printf("%d", vis[l]);
            return 0;
        }
        auto itx1 = upper_bound(all(cdx), cur);
        auto itx2 = lower_bound(all(cdx), cur);
        auto ity1 = upper_bound(all(cdy), cur, cmpy);
        auto ity2 = lower_bound(all(cdy), cur, cmpy);
        if(itx2 != cdx.begin() && !vis.count(convert(*(itx2 - 1)))) {
            block tmp = *(itx2 - 1);
            if(tmp.x == cur.x) {
                Q.push(tmp);
                vis[convert(tmp)] = vis[l] + !tmp.z;
            }
        }
        if(itx1 != cdx.end() && !vis.count(convert(*itx1))) {
            block tmp = *itx1;
            if(tmp.x == cur.x) {
                Q.push(tmp);
                vis[convert(tmp)] = vis[l] + !tmp.z;
            }
        }
        if(ity2 != cdy.begin() && !vis.count(convert(*(ity2 - 1)))) {
            block tmp = *(ity2 - 1);
            if(tmp.y == cur.y) {
                Q.push(tmp);
                vis[convert(tmp)] = vis[l] + !tmp.z;
            }
        }
        if(ity1 != cdy.end() && !vis.count(convert(*ity1))) {
            block tmp = *ity1;
            if(tmp.y == cur.y) {
                Q.push(tmp);
                vis[convert(tmp)] = vis[l] + !tmp.z;
            }
        }
    }
    printf("-1");
    return 0;
}
