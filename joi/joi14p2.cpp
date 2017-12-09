#include<bits/stdc++.h>
#include<bits/extc++.h>
// Split T into 3 cases
// Note that after the last number n such that min(A,B) <= n < max(A,B)
// All flips are just counted as normal
#define all(x) x.begin(),x.end()
typedef std::pair<int,int> pii;
typedef long long ll;
const int MAXN=2e5+4;
int N,K,T[MAXN],ind[MAXN*3],swp[MAXN],bit[MAXN*3],st[MAXN*6];
pii C[MAXN],lst[MAXN];
std::vector<int>V;
std::bitset<MAXN>init;
ll ans;
inline void build() {
    for(int i=V.size()-1;i;i--)st[i]=std::max(st[i<<1],st[i<<1|1]);
}
inline int query(int l,int r) {
    int res=-1;
    for(l+=V.size(),r+=V.size();l<r;l>>=1,r>>=1) {
        if(l&1) res=std::max(res,st[l++]);
        if(r&1) res=std::max(st[--r],res);
    }
    return res;
}
inline void upd(int i,int v) {
    for(;i<MAXN*3;i+=i&-i) bit[i]+=v;
}
inline int query(int i) {
    int res=0;
    for(;i;i-=i&-i) res+=bit[i];
    return res;
}
int main() {
    scanf("%d%d",&N,&K);
    for(int i=0;i<N;++i) {
        scanf("%d%d",&C[i].first,&C[i].second);
        V.emplace_back(C[i].first);
        V.emplace_back(C[i].second);
    }
    for(int i=0;i<K;++i) {
        scanf("%d",T+i);
        V.emplace_back(T[i]);
    }
    std::sort(all(V));
    V.erase(std::unique(all(V)),V.end());
    memset(ind,-1,sizeof ind);
    for(int i=0;i<K;++i)
        ind[std::lower_bound(all(V),T[i])-V.begin()]=i;
    for(int i=0;i<V.size();++i)
        st[i+V.size()]=ind[i];
    build();
    // Do last part offline
    for(int i=0,l,r;i<N;++i) {
        l=std::lower_bound(all(V),C[i].first)-V.begin();
        r=std::lower_bound(all(V),C[i].second)-V.begin();
        if(r<l) std::swap(l,r);
        lst[i]={query(l,r),i};
    }
    std::sort(lst,lst+N,std::greater<pii>());
    for(int i=K-1,j=0,k=0;j<N;++j) {
        while(i>=0&&i>=lst[j].first) {
            int t=std::lower_bound(all(V),T[i--])-V.begin();
            upd(t+1,1);
            ++k;
        }
        int t=std::lower_bound(all(V),std::max(C[lst[j].second].first,C[lst[j].second].second))-V.begin();
        if(!~lst[j].first)
            //All flips count
            init[lst[j].second]=1;
        swp[lst[j].second]=k-query(t);
    }
    for(int i=0;i<N;++i)
        if(init[i]) {
            if(swp[i]&1)
                ans+=C[i].second;
            else
                ans+=C[i].first;
        } else {
            if(swp[i]&1)
                ans+=std::min(C[i].first,C[i].second);
            else
                ans+=std::max(C[i].first,C[i].second);
        }
    printf("%lld",ans);
}
