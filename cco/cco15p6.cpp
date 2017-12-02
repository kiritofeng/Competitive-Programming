#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
struct rect {
    int a,b,c,d;
    rect(int aa,int bb,int cc,int dd):a(aa),b(bb),c(cc),d(dd){}
    void intersect(rect r) {
        a=max(a,r.a);
        b=max(b,r.b);
        c=min(c,r.c);
        d=min(d,r.d);
    }
    bool valid() {
        return a<=c&&b<=d;
    }
};
const int MAXN = 2504,MAXVAL=1e5+4;
int N, M, K, T, grid[MAXN][MAXN];
pii sh[4];
ll bit[MAXVAL];
set<int>digs[MAXN];
inline bool chk_bit(int m,int i) {
    return m&(1<<i);
}
inline void update(int i,int v) {
    for(;i<MAXVAL;i+=i&-i) {
         bit[i]+=v;
    }
}
inline ll query(int i) {
    ll res=0;
    for(;i;i-=i&-i) res+=bit[i];
    return res;
}
int main() {
    scanf("%d%d", &N, &K);
    scanf("%d", &M);
    for(int i=0, S;i<M;i++) {
        scanf("%d", &S);
        for(int j=0;j<S;j++)
            scanf("%d%d",&sh[j].first,&sh[j].second);
        for(int j=1,cnt;j<(1<<S);j++) {
            cnt=0;
            rect r=rect(1,1,N,N);
            for(int k=0;k<S;k++) {
                if(chk_bit(j,k)) {
                    r.intersect(rect(sh[k].first-K+1,sh[k].second-K+1,sh[k].first,sh[k].second));
                    ++cnt;
                }
            }
            if(r.valid())
                if(cnt&1) {
                    //Add
                    grid[r.a][r.b]++;
                    grid[r.a][r.d+1]--;
                    grid[r.c+1][r.b]--;
                    grid[r.c+1][r.d+1]++;
                } else {
                    //Subtract
                    grid[r.a][r.b]--;
                    grid[r.a][r.d+1]++;
                    grid[r.c+1][r.b]++;
                    grid[r.c+1][r.d+1]--;
                }
        }
    }
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            grid[i][j]+=grid[i-1][j]-grid[i-1][j-1]+grid[i][j-1];
    for(int i=1;i<=N-K+1;i++)
        for(int j=1;j<=N-K+1;j++)
            if(grid[i][j]) {
                digs[i].insert(j);
                update(grid[i][j],1);
            }
    scanf("%d",&T);
    for(int i=0,a,b,c;i<T;i++) {
        scanf("%d",&a);
        switch(a) {
            case 1:
                scanf("%d%d",&b,&c);
                for(int j=max(b-K+1,1);j<=b;j++) {
                    auto it = digs[j].lower_bound(max(1,c-K+1));
                    while(it!=digs[j].end()&&*it<=c) {
                        update(grid[j][*it],-1);
                        it=digs[j].erase(it);
                    }
                }
                break;
            case 2:
                scanf("%d",&b);
                if(b>M)
                    printf("0.0\n");
                else
                    printf("%.6f\n",1.0*(query(MAXVAL-1)-query(b-1))/((N-K+1)*(N-K+1)));
                break;
        }
    }
}
