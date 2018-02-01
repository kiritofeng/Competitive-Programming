#include<bits/stdc++.h>
const int MN=1e6+4,MB=22;
int N,A[MN],ans[1<<MB];
inline int inv(int i){
    return ((1<<MB)-1)&~i;
}
int main(){
    scanf("%d",&N);
    memset(ans,-1,sizeof ans);
    for(int i=0;i<N;++i){
        scanf("%d",A+i);
        ans[A[i]]=A[i];
    }
    for(int i=0;i<MB;++i)
        for(int j=0;!(j>>MB);++j)
            if(j&(1<<i))
                ans[j]=std::max(ans[j],ans[j^(1<<i)]);
    for(int i=0;i<N;++i)
        printf("%d ",ans[inv(A[i])]);
}
