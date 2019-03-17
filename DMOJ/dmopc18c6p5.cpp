#include<bits/stdc++.h>
#define allOf(v) v.begin(), v.end()
typedef std::pair<int,int>pii;
typedef long long ll;
const int MK=1e5+4,MQ=1e5+4;
struct rect {
    int r1,c1,r2,c2;;
}pics[MQ];
int N,M,K,Q,T,mx[MK];
ll ans;
pii geese[MK];
// geese is 0, picture is 1 and -1
struct evt{
    int x,y1,y2,val,tp,ind;
    evt(int _x,int _y1,int _y2,int _val,int _ind):x(_x),y1(_y1),y2(_y2),val(_val),ind(_ind){}
    inline bool operator < (const evt &e) const {
        return x<e.x or (x==e.x and val>e.val);
    }
};
struct nd {
    int l,r,mx,lz;
}sgt[MK+MQ<<3];
std::vector<evt>evts;
std::vector<int>pnts;
inline void psh(int i) {
    sgt[i<<1].mx+=sgt[i].lz;
    sgt[i<<1].lz+=sgt[i].lz;
    sgt[i<<1|1].mx+=sgt[i].lz;
    sgt[i<<1|1].lz+=sgt[i].lz;
    sgt[i].lz=0;
}
inline void upd(int i) {
    sgt[i].mx=std::max(sgt[i<<1].mx,sgt[i<<1|1].mx);
}
void build(int l,int r,int i=1) {
    sgt[i].l=l,sgt[i].r=r;
    if(l==r) return;
    int mid=l+r>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
}
int qry(int l,int r,int i=1) {
    if(l>sgt[i].r or r<sgt[i].l) return 0;
    if(l<=sgt[i].l and sgt[i].r<=r) {
        return sgt[i].mx;
    }
    if(sgt[i].lz) psh(i);
    int ret=std::max(qry(l,r,i<<1),qry(l,r,i<<1|1));
    upd(i);
    return ret;
}
void mod(int l,int r,int v,int i=1) {
    if(l>sgt[i].r or r<sgt[i].l) return;
    if(l<=sgt[i].l and sgt[i].r<=r) {
        sgt[i].mx+=v;
        sgt[i].lz+=v;
        return;
    }
    if(sgt[i].lz) psh(i);
    mod(l,r,v,i<<1), mod(l,r,v,i<<1|1);
    upd(i);
}
inline int cmprs(int i) {
    return std::lower_bound(allOf(pnts),i)-pnts.begin();
}
inline void solve() {
    evts.clear();
    pnts.clear();
    for(int i=0;i<K;++i) {
        evts.emplace_back(geese[i].first,geese[i].second-T,geese[i].second+T,0,i);
        pnts.push_back(geese[i].second-T);
        pnts.push_back(geese[i].second+T);
    }
    for(int i=0;i<Q;++i) {
        evts.emplace_back(pics[i].r1,pics[i].c1,pics[i].c2,1,i);
        evts.emplace_back(pics[i].r2,pics[i].c1,pics[i].c2,-1,i);
        pnts.push_back(pics[i].c1);
        pnts.push_back(pics[i].c2);
    }
    std::sort(allOf(evts));
    std::sort(allOf(pnts));
    pnts.erase(std::unique(allOf(pnts)),pnts.end());
    build(0,pnts.size()-1);
    for(auto a:evts) {
        if(a.val) mod(cmprs(a.y1),cmprs(a.y2),a.val);
        else mx[a.ind] = std::max(mx[a.ind], qry(cmprs(a.y1),cmprs(a.y2)));
    }
}
inline void rot() {
    for(int i=0;i<K;++i)
        std::swap(geese[i].first,geese[i].second);
    for(int i=0;i<Q;++i) {
        std::swap(pics[i].r1,pics[i].c1);
        std::swap(pics[i].r2,pics[i].c2);
    }
}
int main() {
    scanf("%d%d%d%d%d",&N,&M,&K,&Q,&T);
    for(int i=0;i<K;++i)
        scanf("%d%d",&geese[i].first,&geese[i].second);
    for(int i=0;i<Q;++i)
        scanf("%d%d%d%d",&pics[i].r1,&pics[i].c1,&pics[i].r2,&pics[i].c2);
    solve();
    rot();
    solve();
    for(int i=0;i<K;++i)
        ans += mx[i];
    printf("%lld\n",ans);
}
