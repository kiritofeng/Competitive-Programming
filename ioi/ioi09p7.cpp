#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,avx,abm,mmx,popcnt,tune=native"
#include<bits/stdc++.h>
#define allOf(v) v.begin(),v.end()
const int MN=2e5+4,RN=400,RN2=500;
int N,R,Q,cnt[MN],col[MN],*cache[RN2];
int icnt,ind[MN];
std::vector<int>adj[MN];
// Euler Tour
int ecnt,eid[MN],ein[MN],eout[MN];
std::vector<int>et[MN];
void dfs1(int src,int par) {
    eid[ein[src]=++ecnt]=src;
    et[col[src]].push_back(ein[src]);
    for(int i:adj[src]) {
        if(i==par) continue;
        dfs1(i,src);
    }
    eout[src]=ecnt;
}
void dfs2(int src,int par,int cl,int id,int anc) {
    cache[id][col[src]]+=anc;
    anc+=(col[src]==cl);
    for(int i:adj[src]) {
        if(i==par) continue;
        dfs2(i,src,cl,id,anc);
    }
}
int main() {
    scanf("%d%d%d",&N,&R,&Q);
    scanf("%d",&col[1]);
    ++cnt[col[1]];
    for(int i=2,p;i<=N;++i) {
        scanf("%d%d",&p,&col[i]);
        adj[i].push_back(p);
        adj[p].push_back(i);
        ++cnt[col[i]];
    }
    dfs1(1,0);
    memset(ind,-1,sizeof ind);
    for(int i=1;i<=R;++i) {
        if(cnt[i]>=RN) {
            ind[i]=icnt;
            cache[icnt]=(int*)calloc(N+1,sizeof(int));
            dfs2(1,0,i,icnt++,0);
        }
    }
    for(int i=0,a,b;i<Q;++i) {
        scanf("%d%d",&a,&b);
        if(~ind[a]) {
            printf("%d\n",cache[ind[a]][b]);
        } else {
            int ans=0;
            for(int j:et[a]) {
                ans+=std::upper_bound(allOf(et[b]),eout[eid[j]])-std::lower_bound(allOf(et[b]),ein[eid[j]]);
            }
            printf("%d\n",ans);
            fflush(stdout);
        }
    }
}
