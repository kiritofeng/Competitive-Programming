#include<bits/stdc++.h>
typedef long long ll;
typedef std::pair<int,int>pii;
const int MN=20004,MM=500004,MQ=50004,LQ=16,inf=0x3f3f3f3f;
int N,M,Q,cnt,X[MM],Y[MM],Z[MM][2],inv[MM];
ll ans[MQ];
struct seg{
    int l,r,id,wei;
};
std::vector<seg>V;
struct nd{
    int id,wei,ind,mx,mxind;
    bool rev;
    nd *p,*ch[2];
    nd(int i,int ii,int w):id(i),wei(w),ind(ii),mx(w),mxind(ii),rev(0),p(0),ch{0}{}
}*lct[MN+(MM+MQ)*LQ*2];
inline bool par(nd *n) {
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}
inline void psh(nd *n) {
    if(n->rev) {
        std::swap(n->ch[0],n->ch[1]);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
}
inline int mx(nd *n) {
    return n?n->mx:-inf;
}
inline void upd(nd *n) {
    n->mx=std::max(std::max(mx(n->ch[0]),mx(n->ch[1])),n->wei);
    if(n->mx==mx(n->ch[0])) n->mxind = n->ch[0]->mxind;
    else if(n->mx==mx(n->ch[1])) n->mxind = n->ch[1]->mxind;
    else n->mxind = n->ind;
}
inline void rot(nd *n,bool b) {
    nd *p=n->p;
    if(p->ch[!b]=n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p) {
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    upd(n->ch[b]=p);
}
inline void splay(nd *n) {
    while(par(n)) {
        bool p=par(n->p);
        if(p) psh(n->p->p);
        psh(n->p), psh(n);
        if(p) {
            bool b=n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n,!b),rot(n,b);
            else rot(n->p,b),rot(n,b);
        } else rot(n,n->p->ch[0]==n);
    }
    psh(n);
    upd(n);
}
inline nd *access(nd *u) {
    nd *l=0;
    for(nd *v=u;v;v=v->p) {
        splay(v);
        v->ch[1]=l;
        l=v;
    }
    splay(u);
    return l;
}
inline void evert(nd *u) {
    access(u);
    u->rev^=1;
}
inline bool con(nd *u,nd *v) {
    if(u==v) return 1;
    access(u);
    access(v);
    return u->p;
}
inline void lnk(nd *u,nd *v) {
    evert(u);
    u->p=v;
}
inline void cut(nd *u,nd *v) {
    evert(u);
    access(v);
    if(!v->ch[0]) return;
    v->ch[0]->p=0;
    v->ch[0]=0;
    upd(v);
}
inline int qry(nd *u,nd *v) {
    if(!con(u,v)) return -1;
    evert(u);
    access(v);
    return v->mxind;
}
inline void add(int i) {
    lnk(lct[i],lct[X[lct[i]->id]]);
    lnk(lct[i],lct[Y[lct[i]->id]]);
}
inline void del(int i) {
    cut(lct[i],lct[X[lct[i]->id]]);
    cut(lct[i],lct[Y[lct[i]->id]]);
}
// dynamic MST when you only add edges is trivial
// so just add an O(log N) layer and you're done!
void solve(int l,int r,std::vector<seg> &v, ll res) {
    // divide and conquer
    std::vector<seg> vl,vr,stk;
    std::vector<int>rem;
    std::vector<pii>old;
    for(seg &s:v) {
        if(s.r < l or s.l > r) continue;
        if(s.l <= l and r <= s.r) {
            int id = qry(lct[X[s.id]],lct[Y[s.id]]);
            if(id >= 0) {
                int wei = Z[lct[id]->id][0];
                if(wei <= s.wei)  // we can safely ignore this update
                    continue;
                del(id);
                res -= wei;
            }
            // memorize what to restore
            stk.push_back(s);
            rem.push_back(id);
            old.push_back({++cnt, Z[s.id][0]});
            lct[cnt] = new nd(s.id, cnt, s.wei);
            // add to MST
            add(cnt);
            res += s.wei;
            // update weight
            Z[s.id][0] = s.wei;
            continue;
        }
        vl.push_back(s);
        vr.push_back(s);
    }
    if(l != r) {
        int m = l + r >> 1;
        solve(l, m, vl, res);
        solve(m + 1, r, vr, res);
    } else {
        ans[l] = res;
    }
    for(int i=stk.size()-1;i>=0;--i) {
        auto s = stk[i];
        auto r = rem[i];
        auto o = old[i];
        // restore weight
        Z[s.id][0] = o.second;
        // delete edge
        del(o.first);
        // insert old one back
        if(r >= 0)
            add(r);
    }
}
int main() {
    scanf("%d%d%d",&N,&M,&Q);
    for(int i=1;i<=N;++i) lct[i] = new nd(i,i,-1);
    cnt = N;
    for(int i=1;i<=M;++i) {
        scanf("%d%d%d",&X[i],&Y[i],&Z[i][0]);
        inv[i] = 0;
        Z[i][1] = Z[i][0];
    }
    for(int i=1,a,b;i<=Q;++i) {
        scanf("%d%d",&a,&b);
        V.push_back({inv[a],i-1,a,Z[a][1]});
        inv[a]=i;
        Z[a][1]=b;
    }
    for(int i=1;i<=M;++i) {
        V.push_back({inv[i],Q,i,Z[i][1]});
    }
    solve(1,Q,V,0);
    for(int i=1;i<=Q;++i)
        printf("%lld\n",ans[i]);
}
