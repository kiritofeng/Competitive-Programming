#include<bits/stdc++.h>
#include<bits/extc++.h>
typedef std::pair<double,int>pdi;
const int MAXN=4004;
const double EPS=1e-6;
struct rab{
    int x,y,w;
}R[MAXN];
int N,ans,val;
#define all(x) x.begin(),x.end()
int main() {
    scanf("%d",&N);
    for(int i=0;i<N;++i)
        scanf("%d%d%d",&R[i].x,&R[i].y,&R[i].w);
    for(int i=0;i<N;++i) {
        //Set R[i] as the center
        std::vector<pdi>V;
        for(int j=0;j<N;++j) {
            if(i==j) continue;
            V.emplace_back(atan2(R[j].y-R[i].y,R[j].x-R[i].x),R[j].w);
            V.emplace_back(atan2(R[j].y-R[i].y,R[j].x-R[i].x)+2*M_PI,R[j].w);
        }
        std::sort(all(V));
        val=std::max(R[i].w,0);
        for(int j=0,k=0;j<N;) {
            while(k<2*N&&V[k].first-V[j].first<=M_PI) {
                val+=V[k++].second;
            }
            ans=std::max(ans,val);
            while(j<N&&fabs(V[j+1].first-V[j].first)<=EPS) {
                val-=V[j++].second;
            }
            val-=V[j++].second;
        }
    }
    printf("%d\n",ans);
}
