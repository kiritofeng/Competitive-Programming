#include<bits/stdc++.h>
const int MN = 1e4+4, inf=0x3f3f3f3f;
int N, M, T;
int mx[MN*2], mn[MN*2], ps[MN*2], ss[MN*2], ts[MN*2], bs[MN*2], psa[MN];
inline int calc_mn(int a, int b) {
    return psa[a] <= psa[b] ? a : b;
}
inline int calc_mx(int a, int b) {
    return psa[b] >= psa[a] ? b : a;
}
inline int mn_qry(int l, int r) {
    int ret = l;
    for(l+=N+1,r+=N+1;l<r;l>>=1,r>>=1) {
        if(l & 1) ret = calc_mn(ret, mn[l++]);
        if(r & 1) ret = calc_mn(mn[--r], ret);
    }
    return ret;
}
inline int mx_qry(int l, int r) {
    int ret = l;
    for(l+=N+1,r+=N+1;l<r;l>>=1,r>>=1) {
        if(l & 1) ret = calc_mx(ret, mx[l++]);
        if(r & 1) ret = calc_mx(mx[--r], ret);
    }
    return ret;
}
inline int bs_qry(int l, int r) {
    int lss = -inf, rps = -inf, ret = -inf;
    for(l+=N+1,r+=N+1;l<r;l>>=1,r>>=1) {
        if(l&1) {
            ret = std::max(ret, std::max(bs[l], lss + ps[l]));
            lss = std::max(lss + ts[l], ss[l]);
            ++l;
        }
        if(r&1) {
            --r;
            ret = std::max(ret, std::max(bs[r], ss[r]+rps));
            rps = std::max(ts[r] + rps, ps[r]);
        }
    }
    return std::max(ret, lss + rps);
}
int main() {
    scanf("%d", &T);
    for(int _tc=0;_tc<T;++_tc) {
        scanf("%d",&N);
        ps[N+1] = ss[N+1] = ts[N+1] = bs[N+1] = mn[N+1] = mx[N+1] = 0;
        for(int i=1;i<=N;++i) {
            scanf("%d",&ts[i+N+1]);
            ps[i+N+1] = ss[i+N+1] = bs[i+N+1] = ts[i+N+1];
            psa[i] = ts[i+N+1] + psa[i-1];
            mn[i+N+1] = i;
            mx[i+N+1] = i;
        }
        for(int i=N;i;--i) {
            ts[i] = ts[i<<1] + ts[i<<1|1];
            ps[i] = std::max(ps[i<<1], ts[i<<1] + ps[i<<1|1]);
            ss[i] = std::max(ss[i<<1|1], ts[i<<1|1] + ss[i<<1]);
            bs[i] = std::max(std::max(bs[i<<1], bs[i<<1|1]), ss[i<<1] + ps[i<<1|1]);
            mn[i] = calc_mn(mn[i<<1], mn[i<<1|1]);
            mx[i] = calc_mx(mx[i<<1], mx[i<<1|1]);
        }
        scanf("%d",&M);
        for(int i=0,a,b,c,d;i<M;++i) {
            scanf("%d%d%d%d",&a,&b,&c,&d);
            if(b <= c) {
                printf("%d\n", -psa[mn_qry(a-1,b)] + psa[mx_qry(c,d+1)]);
            } else {
                int s1 = -psa[mn_qry(a-1,c)] + psa[mx_qry(c,d+1)];
                int s2 = -psa[mn_qry(a-1,b)] + psa[mx_qry(b,d+1)];
                int s3 = bs_qry(c,b+1);
                printf("%d\n", std::max(std::max(s1, s2), s3));
            }
        }
    }
}
