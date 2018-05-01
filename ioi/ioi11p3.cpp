#include<bits/stdc++.h>
const int MN=1e5+4;
typedef long long ll;
int R,L,lo,hi,mid,*X;
ll B;
inline bool chk(int len){
    std::deque<int>dq;
    ll lft=0,rht=0;
    for(int i=0,j=0,m=0;i<R;++i){
        dq.push_back(X[i]);
        rht+=X[i];
        if(dq.size()&1){
            rht-=dq[dq.size()-1>>1];
            lft+=dq[dq.size()-1>>1];
        }
        while(rht-lft+(dq.size()&1)*dq[dq.size()-1>>1]>B){
            lft-=dq.front();
            dq.pop_front();
            if(dq.size()&1){
                lft+=dq[dq.size()-1>>1];
                rht-=dq[dq.size()-1>>1];
            }
            ++j;
        }
        if(i-j+1>=len) return 1;
    }
    return 0;
}
int besthub(int _R,int _L,int* _X,ll _B){
    R=_R;
    L=_L;
    X=_X;
    B=_B;
    lo=1,hi=R;
    while(lo<=hi){
        mid=lo+hi>>1;
        if(chk(mid)) lo=mid+1;
        else hi=mid-1;
    }
    return hi;
}
#ifndef SIGNATURE_GRADER
int _R,_L,_X[MN];
ll _B;
int main(){
    scanf("%d%d%lld",&_R,&_L,&_B);
    for(int i=0;i<R;scanf("%d",_X+i++));
    printf("%d\n",besthub(_R,_L,_X,_B));
}
#endif
