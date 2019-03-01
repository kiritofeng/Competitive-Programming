#include<bits/stdc++.h>
struct nd{
    int val,sz;
    nd *p,*ch[2];
    nd(int i):val(i),sz(1),p(0){ch[0]=ch[1]=0;}
}*rt;
inline int sz(nd *n){
    return n?n->sz:0;
}
inline void upd(nd *n){
    if(n) n->sz=sz(n->ch[0])+1+sz(n->ch[1]);
}
inline void rot(nd *n,bool b){
    nd *tmp=n->p;
    tmp->ch[!b]=n->ch[b];
    if(n->ch[b])n->ch[b]->p=tmp;
    n->p=tmp->p;
    if (tmp->p){
        if(tmp->p->ch[0]==tmp)n->p->ch[0]=n;
        else if (tmp->p->ch[1]==tmp)n->p->ch[1]=n;
    }
    tmp->p=n;
    n->ch[b]=tmp;
    upd(tmp);
}
inline void splay(nd *n){
    if(!n) return;
    while(n->p){
        if(n->p->p){
            bool b=n->p==n->p->p->ch[0];
            if(n==n->p->ch[b]) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        }else rot(n,n==n->p->ch[0]);
    }
    upd(n);
}
inline void ins(int i){
    if(!rt)rt=new nd(i);
    else{
        nd *tmp=rt;
        while(tmp){
            bool b=tmp->val<=i;
            if(!tmp->ch[b]){
                tmp->ch[b]=new nd(i);
                tmp->ch[b]->p=tmp;
                tmp=tmp->ch[b];
                break;
            }
            tmp=tmp->ch[b];
        }
        splay(rt=tmp);
    }
}
inline void del(int i){
    if(rt){
        nd *tmp=rt;
        while(tmp){
            if(tmp->val==i) break;
            bool b=tmp->val<i;
            if(!tmp->ch[b]) break;
            tmp=tmp->ch[b];
        }
        splay(tmp); 
        if(tmp->val==i){
            nd *n=tmp->ch[0];
            if(!n)n=tmp->ch[1];
            else{
                while(n->ch[1])n=n->ch[1];
                tmp->ch[0]->p=0;
                splay(n);
                n->ch[1]=tmp->ch[1];
                if(n->ch[1])n->ch[1]->p=n;
            }
            if(n){
                n->p=0;
                upd(n);
            }
            rt=n;
            delete tmp;
        }else rt=tmp;
    }
}
inline int sel(int i){
    if(!rt) return -1;
    nd *n=rt;
    while(n){
        if(i==sz(n->ch[0])+1)break;
        bool b=sz(n->ch[0])+1<i;
        if(b) i-=sz(n->ch[0])+1;
        if(!n->ch[b]) break;
        n=n->ch[b];
    }
    splay(rt=n);
    return n->val;
}
inline int rnk(int i) {
    if(!rt) return -1;
    nd *ans=0,*n=rt;
    while(n){
        if(n->val==i)ans=n;
        bool b=n->val<i;
        if(!n->ch[b])break;
        n=n->ch[b];
    }
    if(!ans)ans=n;
    splay(rt=ans);
    if(ans->val!=i) return -1; 
    return sz(ans->ch[0])+1;
}
void dfs(nd *n){
    if(!n) return;
    dfs(n->ch[0]);
    printf("%d ",n->val);
    dfs(n->ch[1]);
}
int N,M,ans;
char c;
int main() {
    scanf("%d%d",&N,&M);
    for(int i=0,a;i<N;++i){
        scanf("%d",&a);
        ins(a);
    }
    for(int i=0,a;i<M;++i){
        scanf(" %c%d",&c,&a);
        a^=ans;
        if(c=='I') ins(a);  
        else if(c=='R') del(a);
        else if(c=='S') printf("%d\n",ans=sel(a));
        else printf("%d\n",ans=rnk(a));
    }
    dfs(rt);
}
