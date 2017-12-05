#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+4;
int N, M, L[MAXN], C[MAXN];
long long ans, sum[MAXN];
vector<int> adj[MAXN];
struct node{
   int val,sz;
   node *ch[2];
   node(int i):val(i),sz(1){ch[0]=ch[1]=0;}
}*hp[MAXN];
inline int sz(node *n) {
    return n?n->sz:0;
}
inline void upd(node *x) {
    if(x)x->sz=sz(x->ch[0])+1+sz(x->ch[1]);
}
node* meld(node *x, node *y) {
    if (!x||!y) return x?x: y;
    if (C[x->val]<C[y->val]) swap(x, y);
    bool b=rand()&1;
    x->ch[b]=meld(y, x->ch[b]);
    upd(x);
    return x;
}
void ins(node *&n, int i) {
    n=meld(n,new node(i));
}
void del(node *&n) {
    node *tmp=n;
    n=meld(n->ch[0],n->ch[1]);
    free(tmp);
}
int top(node *n) {
    return n->val;
}
void DFS(int src) {
    for (int i: adj[src]) {
        DFS(i);
        sum[src]+=sum[i];
        hp[src]=meld(hp[src],hp[i]);
    }
    while(sum[src]>M) {
        sum[src]-=C[top(hp[src])];
        del(hp[src]);
    }
    ans=max(ans, 1LL*L[src]*sz(hp[src]));
}
int main() {
    scanf("%d%d", &N, &M);
    for (int i=1,b;i<=N;++i) {
        scanf("%d%d%d", &b, &C[i], &L[i]);
        adj[b].push_back(i);
        ins(hp[i], i);
        sum[i]+=C[i];
    }
    DFS(1);
    printf("%lld",ans);
}
