#include <bits/stdc++.h>
typedef long long ll;
const int MAXSZ = 200004, MAXP = 24;
int P,Q,N,X,pw[MAXP],rating[MAXP];
ll psa[MAXSZ];
int get_ind() {
    int ind=0;
    for(int i=P-1;i>=0;--i)
        ind+=pw[i]*(Q-rating[i]-1);
    return ind;
}
void sum() {
    for(int i=0;i<P;++i) {
        //Sum dimension i
        for(int j=pw[i];j<MAXSZ;++j) {
            if((j-pw[i])/pw[i+1]==j/pw[i+1]) {
                psa[j]+=psa[j-pw[i]];
            }
        }
    }
}
int main() {
    scanf("%d%d%d",&P,&Q,&N);
    pw[0]=1;
    for(int i=1;i<=P;++i)
        pw[i]=pw[i-1]*Q;
    for(int i=0;i<N;++i) {
        for(int j=0;j<P;++j)
            scanf("%d",&rating[j]);
        ++psa[get_ind()];
    }
    sum();
    scanf("%d",&X);
    for(int i=0;i<X;++i) {
        for(int j=0;j<P;++j)
            scanf("%d",&rating[j]);
        printf("%lld\n",psa[get_ind()]);
    }
}
