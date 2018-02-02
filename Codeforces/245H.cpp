#include<bits/stdc++.h>
typedef long long ll;
const int ML=5004,sd1=131,mod1=1e9+7,sd2=31,mod2=1e9+3;
int Q,len,psa[ML][ML];
ll pw[ML][2],hsh[ML][4];
char S[ML];
inline ll ghsh(int l,int r,int i){
    if(i&1)
        return ((hsh[r][i]-hsh[l][i]*pw[abs(r-l)][i&1])%mod2+mod2)%mod2;
    else
        return ((hsh[r][i]-hsh[l][i]*pw[abs(r-l)][i&1])%mod1+mod1)%mod1;
}
inline bool isPal(int l,int r){
    return ghsh(l-1,r,0)==ghsh(r+1,l,2)&&ghsh(l-1,r,1)==ghsh(r+1,l,3);
}
int main(){
    scanf("%s",S+1);
    len=strlen(S+1);
    pw[0][0]=pw[0][1]=1;
    for(int i=1;i<=len;++i){
        pw[i][0]=(pw[i-1][0]*sd1)%mod1;
        pw[i][1]=(pw[i-1][1]*sd2)%mod2;
        hsh[i][0]=(hsh[i-1][0]*sd1+S[i]-'a'+1)%mod1;
        hsh[i][1]=(hsh[i-1][1]*sd2+S[i]-'a'+1)%mod2;
    }
    for(int i=len;i;--i){
        hsh[i][2]=(hsh[i+1][2]*sd1+S[i]-'a'+1)%mod1;
        hsh[i][3]=(hsh[i+1][3]*sd2+S[i]-'a'+1)%mod2;
    }
    for(int i=1;i<=len;++i)
        for(int j=i;j<=len;++j)
            psa[i][j]=isPal(i,j);
    for(int i=1;i<=len;++i)
        for(int j=1;j<=len;++j)
            psa[i][j]+=psa[i][j-1]-psa[i-1][j-1]+psa[i-1][j];
    scanf("%d",&Q);
    for(int i=0,a,b;i<Q;++i){
        scanf("%d%d",&a,&b);
        printf("%d\n",psa[b][b]-psa[b][a-1]-psa[a-1][b]+psa[a-1][a-1]);
    }
}
