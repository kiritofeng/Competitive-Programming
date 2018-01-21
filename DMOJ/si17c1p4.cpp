#include<bits/stdc++.h>
#include<bits/extc++.h>
const int ML=1e5+4;
int ans,last,ecnt,lnk[ML<<1],len[ML<<1],term[ML<<1],edges[ML<<1][26];
char A[ML],B[ML];
int main(){
    scanf("%s%s",A,B);
    memset(edges,-1,sizeof edges);
    lnk[ecnt++]=-1;
    for(int i=0;A[i];++i){
        len[ecnt]=i+1;
        int r=ecnt++;
        int p=last;
        while(~p&&!~edges[p][A[i]-'a']){
            edges[p][A[i]-'a']=r;
            p=lnk[p];
        }
        if(~p){
            int q=edges[p][A[i]-'a'];
            if(len[p]+1==len[q])
                lnk[r]=q;
            else{
                memcpy(edges[ecnt],edges[q],sizeof edges[q]);
                len[ecnt]=len[p]+1;
                lnk[ecnt]=lnk[q];
                int tmp=ecnt++;
                lnk[q]=lnk[r]=tmp;
                while(~p&&edges[p][A[i]-'a']==q){
                    edges[p][A[i]-'a']=tmp;
                    p=lnk[p];
                }
            }
        }
        last=r;
    }
    for(int i=0,tmp=0,len=0;B[i];){
        if(!~edges[tmp][B[i]-'a']){
            if(!len) return puts("-1")&&0;
            ++ans;
            tmp=0;
            len=0;
        }else{
            tmp=edges[tmp][B[i]-'a'];
            ++len;
            ++i;
        }
    }
    printf("%d",ans+1);
}
