// O(N log N) algorithm to find the minimum pairwise distance between N points on Cartesian plane
// Uses line sweep + BBST
#include<bits/stdc++.h>
typedef long long ll;
const int MN=1e5+4;
const ll LINF=1e15; //not your tradional infinity, since 2 * LINF has to still fit in a long long
int N;
// standard point class, stolen off some cf blog post
struct pnt{
    ll x,y;
    pnt():x(0),y(0){}
    pnt(ll i,ll j):x(i),y(j){}
    inline bool operator <(const pnt &p)const{
        return x<p.x||(x==p.x&&y<p.y);
    }
    inline pnt operator +(const pnt &p){
        return pnt(x+p.x,y+p.y);
    }
    inline pnt operator -(const pnt &p){
        return pnt(x-p.x,y-p.y);
    }
    inline ll operator *(const pnt &p){
        return x*p.x+y*p.y;
    }
    inline ll operator ^(const pnt &p){
        return x*p.y-y*p.x;
    }
}P[MN];
// squared distance, to avoid floating point cancer
inline ll dist(const pnt &p1,const pnt &p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
// comparator to sort by y-coordinate
struct ycmp{
    inline bool operator ()(const pnt &p1,const pnt &p2)const{
        return p1.y<p2.y||(p1.y==p2.y&&p1.x<p2.x);
    }
};
ll ans=LINF;
// sorted by y-coordinate
// can replace with std::set to optimize
std::multiset<pnt,ycmp>bbst;
int main(){
    // read input
    scanf("%d",&N);
    for(int i=0;i<N;++i)
        scanf("%lld%lld",&P[i].x,&P[i].y);
    // sort points by x-coordinate
    std::sort(P,P+N);
    for(int i=0,j=0;i<N;++i){
        while(j<i&&P[i].x-P[j].x>ans)
            // these points should not be considered
            // so remove them from the active set
            bbst.erase(bbst.lower_bound(P[j++]));
        for(auto x=bbst.lower_bound(pnt(P[i].x-ans,P[i].y-ans));x!=bbst.end()&&x->y<=P[i].y+ans;++x)
            // this algorithm looks like it should take O(N^2), but the number of iterations is actually constant
            ans=std::min(ans,dist(P[i],*x));
        // insert into the active set
        bbst.insert(P[i]);
    }
    printf("%lld\n",ans);
}
