#include <bits/stdc++.h>

using namespace std;

char a, b;
bool adj[28][28];
bool vis[28];
vector<pair<int, int> >edges;
vector<pair<int, int> >valid;

void dfs(int src) {
    vis[src]=1;
    for(int i=0;i<=26;i++) {
        if(adj[src][i]&&!vis[i]) dfs(i);
    }
}

int main() {
    scanf(" %c%c", &a, &b);
    while(a^'*') {
        adj[a-'A'][b-'A']=1;
        adj[b-'A'][a-'A']=1;
        edges.push_back({a, b});
        scanf(" %c%c", &a, &b);
    }
    for(pair<int, int> e:edges) {
        memset(vis, 0, sizeof(vis));
        adj[e.first-'A'][e.second-'A']=0;
        adj[e.second-'A'][e.first-'A']=0;
        dfs(0);
        if(! vis[1]) valid.push_back({e.first, e.second});
        adj[e.first-'A'][e.second-'A']=1;
        adj[e.second-'A'][e.first-'A']=1;
    }
    for(pair<int, int> p:valid) {
        printf("%c%c\n", p.first, p.second);
    }

    printf("There are %d disconnecting roads.", valid.size());
}
