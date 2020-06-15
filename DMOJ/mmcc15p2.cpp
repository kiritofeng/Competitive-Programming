#include<bits/stdc++.h>
typedef long long ll;
const int MN=5e5+4,MM=5e5+4;
int N, M, lo[MM], hi[MM];
struct ln{
    int A, B, C, i;
}lns[MN];
inline std::ostream &operator << (std::ostream &os, const ln &l) {
    os << l.A << "x + " << l.B << "y = " << l.C;
    return os;
}
struct qy{
    int X, Y, i;
}qys[MM];
inline std::ostream &operator << (std::ostream &os, const qy &q) {
    os << "(" << q.X << ", " << q.Y << ", " << q.i << ")";
    return os;
}
int uhul[MN], lhul[MN];
#define NUM(a,b) (1LL * lns[b].B * lns[a].C - 1LL * lns[b].C * lns[a].B)
#define DEN(a,b) (1LL * lns[a].A * lns[b].B - 1LL * lns[a].B * lns[b].A)
inline bool lt_frac(ll n1, ll d1, ll n2, ll d2) {
    if(d1 < 0) { n1 *= -1; d1 *= -1; }
    if(d2 < 0) { n2 *= -1; d2 *= -1; }
    return __int128(n1) * __int128(d2) < __int128(n2) * __int128(d1);
}
inline bool gt_frac(ll n1, ll d1, ll n2, ll d2) {
    return lt_frac(n2, d2, n1, d1);
}
inline bool lte_frac(__int128 n1, __int128 d1, __int128 n2, __int128 d2) {
    return !gt_frac(n1, d1, n2, d2);
}
inline bool gte_frac(ll n1, ll d1, ll n2, ll d2) {
    return !lt_frac(n1, d1, n2, d2);
}
inline bool eq_frac(ll n1, ll d1, ll n2, ll d2) {
    return __int128(n1) * __int128(d2) == __int128(n2) * __int128(d1);
}
void solve(int lln, int rln, int lqy, int rqy) {
    lhul[0] = uhul[0] = 0;
    int mid = (lln + rln - 1) >> 1;

    for(int i=lln;i<rln;++i) {
        if(lns[i].i > mid) continue;
        if(uhul[0] && 1LL * lns[uhul[uhul[0]]].A * lns[i].B == 1LL * lns[i].A * lns[uhul[uhul[0]]].B) --uhul[0];
        // intersection of l1 and l2 is
        // (l2.B * l1.C - l2.C * l1.B) / (l1.A * l2.B - l1.B * l2.A)
        while(uhul[0] > 1 && gte_frac(NUM(uhul[uhul[0]-1], uhul[uhul[0]]), DEN(uhul[uhul[0]-1], uhul[uhul[0]]), NUM(uhul[uhul[0]-1], i), DEN(uhul[uhul[0]-1], i)))
            --uhul[0];
        uhul[++uhul[0]] = i;
    }
    for(int i=rln-1;i>=lln;--i) {
        if(lns[i].i > mid) continue;
        if(lhul[0] && 1LL * lns[lhul[lhul[0]]].A * lns[i].B == 1LL * lns[i].A * lns[lhul[lhul[0]]].B) --lhul[0];
        // intersection of l1 and l2 is
        // (l2.B * l1.C - l2.C * l1.B) / (l1.A * l2.B - l1.B * l2.A)
        while(lhul[0] > 1 && gte_frac(NUM(lhul[lhul[0]-1], lhul[lhul[0]]), DEN(lhul[lhul[0]-1], lhul[lhul[0]]), NUM(lhul[lhul[0]-1], i), DEN(lhul[lhul[0]-1], i)))
            --lhul[0];
        lhul[++lhul[0]] = i;
    }
    // now that we have hulls, iterate all points
    for(int i=lqy,lcnt=1,ucnt=1;i<rqy;++i) {
        while(lcnt < lhul[0] && \
                lte_frac(NUM(lhul[lcnt], lhul[lcnt+1]), DEN(lhul[lcnt], lhul[lcnt+1]), qys[i].X, 1)) ++lcnt;
        while(ucnt < uhul[0] && \
                lte_frac(NUM(uhul[ucnt], uhul[ucnt+1]), DEN(uhul[ucnt], uhul[ucnt+1]), qys[i].X, 1)) ++ucnt;

        if(lte_frac(lns[lhul[lcnt]].C - 1LL * lns[lhul[lcnt]].A * qys[i].X, lns[lhul[lcnt]].B, qys[i].Y, 1))
            lo[qys[i].i] = std::min(lo[qys[i].i], mid);
        if(lte_frac(qys[i].Y, 1, lns[uhul[ucnt]].C - 1LL * lns[uhul[ucnt]].A * qys[i].X, lns[uhul[ucnt]].B))
            hi[qys[i].i] = std::min(hi[qys[i].i], mid);
    }
    // do partitioning
    int mln = std::stable_partition(lns+lln, lns+rln, [=](const ln &l) {
                return l.i <= mid;
            }) - lns;
    int mqy = std::stable_partition(qys+lqy, qys+rqy, [=](const qy &q) {
                return hi[q.i] <= mid && lo[q.i] <= mid;
            }) - qys;

    if(lln + 1 == rln) return;
    if(lqy != mqy) solve(lln, mln, lqy, mqy);
    if(mqy != rqy) solve(mln, rln, mqy, rqy);
}
#undef NUM
#undef DEN
int main() {
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;++i) {
        scanf("%d%d%d",&lns[i].A,&lns[i].B,&lns[i].C);
        lns[i].i=i;
    }
    std::sort(lns, lns+N, [=](const ln &l1, const ln &l2) {
                return lt_frac(-l1.A, l1.B, -l2.A, l2.B) || (eq_frac(l1.A, l1.B, l2.A, l2.B) && lt_frac(l1.C, l1.B, l2.C, l2.B));
            });
    for(int i=0;i<M;++i) {
        scanf("%d%d",&qys[i].X,&qys[i].Y);
        qys[i].i=i;
        lo[i] = hi[i] = N;
    }
    std::sort(qys,qys+M,[=](const qy &q1, const qy &q2) {
                return q1.X < q2.X;
            });
    solve(0, N, 0, M);
    for(int i=0;i<M;++i) {
        int ans = std::max(lo[i], hi[i]);
        printf("%d\n", ans < N ? ans + 1 : -1);
    }
}
