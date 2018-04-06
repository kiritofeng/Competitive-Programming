#include<bits/stdc++.h>
const int MN=5e4+4,INF=0x3f3f3f3f;
int N,M,P,dist[MN<<1],pre[MN<<1];
std::vector<int>adj[MN<<1];
inline bool bfs(){
    std::queue<int>Q;
    for(int i=1;i<=N;++i)
        if(!pre[i]){
            dist[i]=0;
            Q.push(i);
        }else dist[i]=INF;
    dist[0]=INF;
    while(!Q.empty()){
        int src=Q.front();
        Q.pop();
        if(dist[src]<dist[0])
            for(int i:adj[src])
                if(dist[pre[i]]==INF){
                    dist[pre[i]]=dist[src]+1;
                    Q.push(pre[i]);
                }
    }
    return dist[0]!=INF;
}
inline bool dfs(int src){
    if(src){
        for(int i:adj[src])
            if(dist[pre[i]]==dist[src]+1)
                if(dfs(pre[i])){
                    pre[i]=src;
                    pre[src]=i;
                    return 1;
                }
        dist[src]=INF;
        return 0;
    }
    return 1;
}
inline int hopcroft_karp(){
    int res=0;
    while(bfs()){
        for(int i=1;i<=N;++i)
            if(!pre[i]) res+=dfs(i);
    }
    return res;
}
int main(){
    scanf("%d%d%d",&N,&M,&P);
    for(int i=0,a,b;i<P;++i){
        scanf("%d%d",&a,&b);
        adj[a].emplace_back(b+N);
        adj[b+N].emplace_back(a);
    }
    printf("%d\n",hopcroft_karp());
}
