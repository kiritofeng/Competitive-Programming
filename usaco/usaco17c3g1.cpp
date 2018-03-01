#include<bits/stdc++.h>
typedef std::pair<int,int>pii;
const int MN=1e5+4,MB=1e5+4;
int N,B,ans[MB],A[MN];
pii arr[MN];
struct boot{
    int s,d,i;
    bool operator <(const boot &b) const{
        return s<b.s;
    }
}boots[MB];
std::multiset<int>S;
std::multiset<int,std::greater<int>>diff;
inline void upd(int pos){
    if(S.empty()){
        S.insert(pos);
        return;
    }
    if(S.size()==1){
        int oth=*S.begin();
        S.insert(pos);
        diff.insert(abs(pos-oth));
        return;
    }
    auto it1=S.lower_bound(pos);
    if(it1==S.end()){
        it1=std::prev(it1);
        diff.insert(pos-*it1);
        S.insert(pos);
        return;
    }
    if(it1==S.begin()){
        diff.insert(*it1-pos);
        S.insert(pos);
        return;
    }
    auto it2=std::prev(it1);
    diff.erase(diff.lower_bound(*it1-*it2));
    diff.insert(*it1-pos);
    diff.insert(pos-*it2);
    S.insert(pos);
}
int main(){
    freopen("snowboots.in","r",stdin);
    freopen("snowboots.out","w",stdout);
    scanf("%d%d",&N,&B);
    for(int i=0;i<N;++i){
        scanf("%d",A+i);
        arr[i]={A[i],i};
    }
    for(int i=0;i<B;++i){
        scanf("%d%d",&boots[i].s,&boots[i].d);
        boots[i].i=i;
    }
    std::sort(arr,arr+N);
    std::sort(boots,boots+B);
    for(int i=0,j=0;i<B;++i){
        while(j<N&&arr[j].first<=boots[i].s)
            upd(arr[j++].second);
        ans[boots[i].i]=*diff.begin()<=boots[i].d;
    }
    for(int i=0;i<B;printf("%d\n",ans[i++]));
}
