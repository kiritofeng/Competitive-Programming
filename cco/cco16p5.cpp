#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

typedef long long ll;

struct line {
    int x, y1, y2, val;

    line(int a, int b, int c, int d) {
        x = a; y1 = b; y2 = c; val = d;
    }
};

bool cmpX(const line &a, const line &b) {
    return a.x < b.x;
}

int N, M, K, Q;
ll ans;
vector<pii>zombies;
vector<line>lines;
vector<int>segy;
unordered_map<int, int>findy;

inline int a1(int i) {
    return max(1, i);
}

inline int an(int i) {
    return min(N, i);
}

inline int am(int i) {
    return min(M, i);
}

int main() {
    scanf("%d%d%d", &N, &M, &K);
    for(int i=0, a, b;i<K;i++) {
        scanf("%d%d", &a, &b);
        zombies.push_back({b, a});
    }
    scanf("%d", &Q);
    for(pii p:zombies) {
        lines.push_back(line(a1(p.first - Q), a1(p.second-Q),an(p.second+Q)+1, 1));
        lines.push_back(line(am(p.first + Q - 1) + 1, a1(p.second-Q + 1), an(p.second+Q-1)+1, 4000));
        lines.push_back(line(a1(p.first - Q + 1), a1(p.second-Q + 1), an(p.second+Q-1)+1, -4000));
        lines.push_back(line(am(p.first + Q) + 1, a1(p.second-Q), an(p.second+Q)+1, -1));
        segy.push_back(a1(p.second-Q));
        segy.push_back(a1(p.second-Q+1));
        segy.push_back(an(p.second+Q-1) + 1);
        segy.push_back(an(p.second+Q) + 1);
    }
    sort(lines.begin(), lines.end(), cmpX);
    sort(segy.begin(), segy.end());
    segy.erase(unique(segy.begin(), segy.end()), segy.end());
    for(int i=0;i<segy.size();i++) {
        findy[segy[i]] = i;
    }
    int yaxis[segy.size()];
    memset(yaxis, 0, sizeof(yaxis));
    for(int j = findy[lines[0].y1]; j < findy[lines[0].y2]; j++) {
        yaxis[j] = lines[0].val;
    }
    for(int i = 1;i<lines.size();i++) {
        for(int j=0;j<segy.size() - 1;j++) {
            if(yaxis[j]>0)
                ans += (ll) (segy[j + 1]-segy[j]) * (lines[i].x-lines[i-1].x);
        }
        for(int j=findy[lines[i].y1];j<findy[lines[i].y2];j++) {
            yaxis[j] += lines[i].val;
        }
    }
    printf("%lld", ans);
}
