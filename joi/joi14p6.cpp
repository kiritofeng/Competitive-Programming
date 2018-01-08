#include<bits/stdc++.h>
#include<bits/extc++.h>
#define mp std::make_pair
typedef std::pair<int,int> pii;
const int MN=1e3+4;
int memo[MN][MN],pre[MN],depth[MN];
void Init(int N,int* A){
    memset(memo,-1,sizeof memo);
    for(int i=0;i<N;++i)
        memo[i][i]=A[i];
    std::queue<std::pair<pii,int>>Q;
    Q.push({{0,N-1},-1});
    while(!Q.empty()){
        pii seg;int p,mid;
        std::tie(seg,p)=Q.front();
        Q.pop();
        if(seg.first>seg.second) continue;
        mid=seg.first+seg.second>>1;
        depth[mid]=~p?depth[p]+1:1;
        pre[mid]=p;
        Q.push(mp(mp(seg.first,mid-1),mid));
        Q.push(mp(mp(mid+1,seg.second),mid));
    }
    int m=*std::max_element(depth,depth+N);
    for(int i=1,j,k;i<=m;++i){
        j=0;
        while(j<N){
            k=j;    // keep starting
            for(;depth[j]>i;++j);
            if(depth[j]<i){
                ++j;
                continue;
            }
            // j is the centroid we care about
            for(int l=j-1;l>=k;--l)
                memo[l][j]=Secret(A[l],memo[l+1][j]);
            for(int l=j+2;depth[l]>i;++l)
                memo[j+1][l]=Secret(memo[j+1][l-1],A[l]);
            ++j;
        }
    }
}
int Query(int L,int R){
    int tmpL=L,tmpR=R;
    while(tmpL!=tmpR){  //get lca
        if(depth[tmpL]<depth[tmpR]) std::swap(tmpL,tmpR);
        tmpL=pre[tmpL];
    }
    if(R==tmpR) return memo[L][R];
    if(L==tmpL) return Secret(memo[L][L],memo[L+1][R]);
    return Secret(memo[L][tmpL],memo[tmpR+1][R]);
}
