#include<bits/extc++.h>
#include<bits/stdc++.h>
typedef long long ll;
const int MOD=1e9;
struct matrix{
    ll A[2][2];
    matrix():A{{1,0},{0,1}}{}
    matrix(ll a,ll b,ll c,ll d):A{{a,b},{c,d}}{}
    inline ll* operator[](int i){
        return A[i];
    }
    inline matrix operator*(matrix m){
        matrix res=matrix(0,0,0,0);
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                for(int k=0;k<2;++k)
                    res[i][j]=(res[i][j]+A[i][k]*m[k][j])%MOD;
        return res;
    }
    inline void operator*=(matrix m){
        *this=(*this)*m;
    }
}m;
inline matrix pow(matrix m,ll e){
    matrix res=matrix();
    while(e){
        if(e&1) res*=m;
        m*=m;
        e>>=1;
    }
    return res;
}
ll N,init[2],res[2];
int main(){
    scanf("%lld%lld%lld",&init[0],&init[1],&N);
    m=matrix(0,1,1,1);
    m=pow(m,N);
    for(int i=0;i<2;++i)
        for(int k=0;k<2;++k)
            res[i]=(res[i]+m[i][k]*init[k])%MOD;
    printf("%lld",res[0]);
}
