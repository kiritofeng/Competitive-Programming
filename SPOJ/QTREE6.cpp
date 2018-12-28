#include<bits/stdc++.h>
const int MN=1e5+4;
int N,Q,C[MN],fa[MN];
std::vector<int>adj[MN];
struct nd{
    int id,val,sum,lz;
    nd *p,*ch[2];
    nd(int i,int v):id(i),val(v),lz(0),p(0),ch{0}{};
}*lct[MN][2];
inline bool par(nd *n) {
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline void psh(nd *n) {
    if(n->lz){
        n->val+=n->lz;
        if(n->ch[0])n->ch[0]->lz+=n->lz;
        if(n->ch[1])n->ch[1]->lz+=n->lz;
        n->lz=0;
    }
}
inline void rot(nd *n,bool b) {
    nd *p=n->p;
    if(p->ch[!b]=n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p) {
        if(p->p->ch[0]==p)n->p->ch[0]=n;
        if(p->p->ch[1]==p)n->p->ch[1]=n;
    }
    p->p=n;
    n->ch[b]=p;
}
inline void splay(nd *n) {
    while(par(n)){
        bool p=par(n->p);
        if(p) psh(n->p->p);
        psh(n->p);psh(n);
        if(p) {
            bool b=n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        } else rot(n,n->p->ch[0]==n);
    }
    psh(n);
}
inline nd *access(nd *u){
    nd *n=0;
    for(nd *v=u;v;v=v->p){
        splay(v);
        v->ch[1]=n;
        n=v;
    }
    splay(u);
    return n;
}
inline nd *mn(nd *n){
    nd *ret=n;
    while(ret->ch[0]){
        ret=ret->ch[0];
    }
    splay(ret);
    return ret;
}
inline nd *rt(nd *n) {
    access(n);
    return mn(n);
}
inline void lnk(nd *u,nd *v) {
    access(v);
    v->p=u;
}
inline void cut(nd *u){
    access(u);
    if(!u->ch[0])return;
    u->ch[0]->p=0;
    u->ch[0]=0;
}
void dfs(int src,int pre) {
    fa[src]=pre;
    for(int i:adj[src]) {
        if(i==pre) continue;
        lnk(lct[src][0],lct[i][0]);
        dfs(i,src);
    }
    access(lct[src][0]);
    lct[src][0]->lz+=1;
}
int main() {
    scanf("%d",&N);
    for(int i=0;i<=N;++i){
        lct[i][0]=new nd(i,0);
        lct[i][1]=new nd(i,1);
    }
    for(int i=1,a,b;i<N;++i) {
        scanf("%d%d",&a,&b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    scanf("%d",&Q);
    for(int i=0,a,b;i<Q;++i) {
        scanf("%d%d",&a,&b);
        if(a) {
            // invert the color
            C[b]^=1;
            if(!fa[b]) continue;
            // cut the old parent
            cut(lct[b][C[b]^1]);
            // access it
            access(lct[fa[b]][C[b]^1]);
            lct[fa[b]][C[b]^1]->lz-=lct[b][C[b]^1]->val;
            // connect to new parent
            lnk(lct[fa[b]][C[b]],lct[b][C[b]]);
            // update the new parent
            access(lct[fa[b]][C[b]]);
            lct[fa[b]][C[b]]->lz+=lct[b][C[b]]->val;
        } else {
            // fetch the root
            int r=rt(lct[b][C[b]])->id;
            if(C[r]==C[b]){
                // include the root
                printf("%d\n",lct[r][C[b]]->val);
            } else {
                // ignore the root itself
                printf("%d\n",mn(lct[r][C[b]]->ch[1])->val);
            }
        }
    }
}
