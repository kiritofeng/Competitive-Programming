// standard headers
#include<queue>
#include<list>
#include<bitset>
const int MN=5001,MM=1e5+1;
short N,cnt,ans[MM];
int M,K,op[MM];
std::bitset<MN>p;
std::list<int>dq,adj[MM];
void dfs(int src){
    ans[src]=p.count()-cnt;
    for(int i:adj[src]){
        char cmd=op[i]>>20;
        int loc=op[i]&((1<<20)-1);
        bool old=p[loc];
        if(cmd=='F'){
            p[loc]=1;
        }else if(cmd=='D'){
            p[loc]=0;
        }else if(cmd=='X'){
            p.flip();
            cnt=MN-N-cnt;
        }
        dfs(i);
        if(cmd=='X'){
            p.flip();
            cnt=MN-N-cnt;
        }else{
            p[loc]=old;
        }
    }
}
int main(){
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1,a=0;i<=M;++i){
        char c;
        scanf(" %c",&c);
        a=0;
        if(c!='X') scanf("%d",&a);
        op[i]=(c<<20)|a;
        if(c=='R'){
            adj[a].emplace_back(i);
        }else{
            adj[i-1].emplace_back(i);
        }
    }
    dfs(0);
    for(int i=1;i<=M;++i){
        while(!dq.empty()&&i-dq.front()>=K)
            dq.pop_front();
        while(!dq.empty()&&ans[dq.back()]<=ans[i])
            dq.pop_back();
        dq.push_back(i);
        printf("%d %d\n",ans[i],ans[dq.front()]);
    }
    return 0;
}
