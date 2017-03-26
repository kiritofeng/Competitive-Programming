#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

template<typename T>
void operator+=(vector<T> &v, const T &t) {
    v.push_back(t);
}

struct problem {
    int st, ed, sc;
};

int B, F, ans;
vector<problem>batches;
vector<int>fail;
int main() {
    scanf("%d", &B);
    for(int i=0, f, e, p;i<B;i++) {
        scanf("%d%d%d", &f, &e, &p);
        assert(f&&e);
        batches += {f, e, p};
    }
    scanf("%d", &F);
    for(int i=0, t;i<F;i++) {
        scanf("%d", &t);
        fail += t;
    }
    sort(fail.begin(), fail.end());
    for(problem p: batches) {
        auto it = lower_bound(fail.begin(), fail.end(), p.st);
        if(it != fail.end() && *it <= p.ed) continue;
        ans += p.sc;
    }
    printf("%d\n", ans);
}
