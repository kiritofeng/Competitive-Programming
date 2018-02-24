#include<bits/stdc++.h>
typedef std::pair<int,int>pii;
const int MN=5e3+4;
int A,B,C,D,N,M,Q,X[2],*T,*loc;
pii *pos;
inline bool find(int r,int c){
    return pos[r].first<=c&&c<=pos[r].second;
}
int main(){
    scanf("%d%d%d%d%d",&X[0],&A,&B,&C,&D);
    scanf("%d%d%d",&N,&M,&Q);
    T = new int[N*M+1];
    for(int i=1;i<=N*M;++i)
        T[i]=i;
    for(int i=1;i<=N*M;++i){
        X[1]=(1LL*A*X[0]*X[0]+1LL*B*X[0]+C)%D;
        std::swap(T[i],T[X[1]%i+1]);
        X[0]=X[1];
    }
    for(int i=0,a,b;i<Q;++i){
        scanf("%d%d",&a,&b);
        std::swap(T[a],T[b]);
    }
    loc = new int[N*M+1];
    for(int i=1;i<=N*M;++i)
        loc[T[i]]=i;
    delete[] T;
    pos=new pii[N];
    printf("%d ",1);
    for(int i=0,r=(loc[1]-1)/M,c=(loc[1]-1)%M+1;i<r;++i)
        pos[i]={1,c};
    pos[(loc[1]-1)/M]={1,M};
    for(int i=(loc[1]-1)/M+1,c=(loc[1]-1)%M+1;i<N;++i)
        pos[i]={c,M};
    for(int i=2,r,c;i<=N*M;++i){
        r=(loc[i]-1)/M,c=(loc[i]-1)%M+1;
        if(find(r,c)){
            printf("%d ",i);
            for(int j=0;j<r;++j)
                pos[j].second=std::min(pos[j].second,c);
            for(int j=r+1;j<N;++j)
                pos[j].first=std::max(pos[j].first,c);
        }
    }
}
