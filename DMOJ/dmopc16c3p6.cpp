#include<bits/stdc++.h>
using namespace std;
const int MAXN=100004,MAXQ=500004;
struct node {
    int val[4];
    node *l, *r;
    node():l(0),r(0){val[0]=val[1]=val[2]=0;};
}*roots[MAXQ];
int N,Q,A[MAXN];
char c;
#define g(a,b) ((a)->val[b])
void inline push_up(node *n) {
    g(n,0)=g(n->l,0)+g(n->r,0);
    g(n,1)=max(g(n->l,1),g(n->l,0)+g(n->r,1));
    g(n,2)=max(g(n->r,2),g(n->r,0)+g(n->l,2));
}
void build(node* &n=roots[0],int l=1,int r=N) {
    n = new node();
    if(l^r) {
        int mid=l+r>>1;
        build(n->l,l,mid);
        build(n->r,mid+1,r);
        push_up(n);
    } else
        g(n,0)=g(n,1)=g(n,2)=A[l];
}
void update(node* &n,node* o,int p,int v,int l=1,int r=N) {
    n = new node();
    if(l^r) {
        int mid=l+r>>1;
        if(p<=mid) {
            update(n->l,o->l,p,v,l,mid);
            n->r=o->r;
        } else {
            update(n->r,o->r,p,v,mid+1,r);
            n->l=o->l;
        }
        push_up(n);
    } else
        g(n,0)=g(n,1)=g(n,2)=v;
}
int query(node *n,int lft,int rht,int i,int l=1,int r=N) {
    if(lft==l&&rht==r)
        return g(n,i);
    int mid=l+r>>1;
    if(rht<=mid)
        return query(n->l,lft,rht,i,l,mid);
    else if(lft>mid)
        return query(n->r,lft,rht,i,mid+1,r);
    else {
        switch(i) {
            case 0:
                return query(n->l,lft,mid,0,l,mid)+query(n->r,mid+1,rht,0,mid+1,r);
            case 1:
                return max(query(n->l,lft,mid,i,l,mid),query(n->l,lft,mid,0,l,mid)+query(n->r,mid+1,rht,1,mid+1,r));
            case 2:
                return max(query(n->r,mid+1,rht,i,mid+1,r),query(n->l,lft,mid,2,l,mid)+query(n->r,mid+1,rht,0,mid+1,r));
        }
    }
}
int main() {
    scanf("%d",&N);
    for(int i=1;i<=N;scanf("%d",A+i++));
    build();
    scanf("%d",&Q);
    for(int i=1,r=0,a,b;i<=Q;++i) {
        scanf(" %c",&c);
        switch(c) {
            case 'U':
                scanf("%d%d",&a,&b);
                update(roots[r+1],roots[r],a,b);
                ++r;
                break;
            case 'G':
                scanf("%d",&a);
                roots[++r]=roots[a];
                break;
            case 'P':
                scanf("%d%d",&a,&b);
                printf("%d\n",query(roots[r],a,b,1));
                break;
            case 'S':
                scanf("%d%d",&a,&b);
                printf("%d\n",query(roots[r],a,b,2));
                break;
        }
    }
}
