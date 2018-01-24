#include<bits/stdc++.h>
typedef long long ll;
typedef std::pair<int,int>pii;
const int MN=1e5+4;
int N,sz[MN],depth[MN],cen[MN],ord[MN],arr[MN<<1],tim[MN<<1];
std::vector<pii>adj[MN];
ll ans;
char c;
inline int get(int val,int t){
    if(tim[val+MN]!=t){
        tim[val+MN]=t;
        return arr[val+MN]=0;
    }
    return arr[val+MN];
}
inline void put(int ind,int val,int t){
    tim[ind+MN]=t;
    arr[ind+MN]=val;
}
void dfs1(int src,int pre,int d){
    sz[src]=1;
    depth[src]=d;
    for(pii &p:adj[src]){
        if(p.first==pre) continue;
        dfs1(p.first,src,d+1);
        sz[src]+=sz[p.first];
    }
}
void dfs2(int src,int s=N,int lvl=1){
    if(cen[src]) return;
    for(pii &p1:adj[src]){
        if(!cen[p1.first]&&sz[p1.first]>s/2){
            sz[src]=1;
            for(pii &p2:adj[src]){
                if(p2.first==p1.first||cen[p2.first]) continue;
                sz[src]+=sz[p2.first];
            }
            dfs2(p1.first,s,lvl);
            return;
        }
    }
    cen[src]=lvl;
    sz[src]=0;
    for(pii &p1:adj[src]){
        if(cen[p1.first]) continue;
        dfs2(p1.first,sz[p1.first],lvl+1);
    }
}
void dfs3(int src,int pre,int sum,int lvl,int t){
    ans+=get(-sum-1,t)+get(-sum+1,t);
    for(pii &p:adj[src]){
        if(cen[p.first]<=lvl||p.first==pre) continue;
        dfs3(p.first,src,sum+p.second,lvl,t);
    }
}
void dfs4(int src,int pre,int sum,int lvl,int t){
    put(sum,get(sum,t)+1,t);
    for(pii &p:adj[src]){
        if(cen[p.first]<=lvl||p.first==pre) continue;
        dfs4(p.first,src,sum+p.second,lvl,t);
    }
}
int main(){
    scanf("%d",&N);
    for(int i=1,a,b;i<N;++i){
        scanf("%d %d %c",&a,&b,&c);
        adj[a].emplace_back(b,(c=='r')-(c=='b'));
        adj[b].emplace_back(a,(c=='r')-(c=='b'));
    }
    dfs1(1,-1,1);
    dfs2(1);
    for(int i=0;i<N;++i) ord[i]=i+1;
    std::sort(ord,ord+N,[=](const int &a,const int &b){
        return cen[a]<cen[b];
    });
    for(int i=0,lst=1,cur,ch;i<N;++i){
        cur=ord[i];
        ch=0;
        for(pii &p:adj[cur]){
            if(cen[p.first]<=cen[cur]) continue;
            dfs3(p.first,cur,p.second,cen[cur],i);
            dfs4(p.first,cur,p.second,cen[cur],i);
            ++ch;
        }
        ans+=get(-1,i)+get(1,i)-ch;
    }
    printf("%lld",ans);
}
