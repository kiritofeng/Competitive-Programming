#include<bits/stdc++.h>
using namespace std;
int N,M,ans;
char c;
struct node {
    int val,p,sz;
    node *ch[2];
    node(int i):val(i),p(rand()),sz(1){ch[0]=ch[1]=0;}
}*root;
inline int sz(node *n) {
    return n?n->sz:0;
}
inline void upd_sz(node *n) {
    if(n) n->sz=sz(n->ch[0])+1+sz(n->ch[1]);
}
void rot(node *&n,bool b) {
    node *tmp=n->ch[b];
    n->ch[b]=tmp->ch[!b];
    tmp->ch[!b]=n;
    upd_sz(n);
    upd_sz(tmp);
    n=tmp;
}
void ins(node *&n, node *i) {
    if(!n)
        n=i;
    else {
        bool b=n->val<i->val;
        ins(n->ch[b],i);
        if(n->ch[b]->p>n->p)
            rot(n,b);
    }
    upd_sz(n);
}
void del(node *&n, int i) {
    if(!n) return;
    if(n->val==i) {
        if(!n->ch[0]||!n->ch[1]) {
            n=n->ch[0]?n->ch[0]:n->ch[1];
        } else {
            bool b=n->ch[1]->p>n->ch[0]->p;
            rot(n,b);
            del(n->ch[!b],i);
        }
    } else
        del(n->ch[n->val<i],i);
    upd_sz(n);
}
int sel(node *n,int i) {
    if(sz(n->ch[0])+1==i) return n->val;
    else if(sz(n->ch[0])+1<i) return sel(n->ch[1],i-sz(n->ch[0])-1);
    else return sel(n->ch[0],i);
}
int rnk(node *n,int i,int s=0) {
    if(!n) return -1;
    if(n->val==i) {
        int tmp=rnk(n->ch[0],i,s);
        return ~tmp?tmp:s+sz(n->ch[0])+1;
    } else if(n->val<i) return rnk(n->ch[1],i,s+1+sz(n->ch[0]));
    else return rnk(n->ch[0],i,s);
}
void traverse(node *n) {
    if(!n) return;
    traverse(n->ch[0]);
    printf("%d ",n->val);
    traverse(n->ch[1]);
}
int main() {
    scanf("%d%d",&N,&M);
    for(int i=0,a;i<N;++i) {
        scanf("%d",&a);
        ins(root,new node(a));
    }
    for(int i=0,x;i<M;++i) {
        scanf(" %c%d",&c,&x);
        x^=ans;
        switch(c) {
            case 'I':
                ins(root,new node(x));
                break;
            case 'R':
                del(root,x);
                break;
            case 'S':
                printf("%d\n",ans=sel(root,x));
                break;
            case 'L':
                printf("%d\n",ans=rnk(root,x));
                break;
        }
    }
    traverse(root);
}
