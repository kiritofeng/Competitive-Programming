#include <bits/stdc++.h>
const int MN=1e5+4;
struct Matrix {
    double a[3][3] = {0};
    double &operator ()(int i, int j) {
        return a[i][j];
    }
    const double &operator ()(int i, int j) const {
        return a[i][j];
    }
    Matrix operator * (const Matrix &m) const {
        Matrix ret;
        for(int i=0;i<3;++i)
            for(int k=0;k<3;++k)
                for(int j=0;j<3;++j)
                    ret(i, j) += a[i][k] * m(k, j);
        return ret;
    }
    static constexpr Matrix id() {
        return Matrix{{{1,0,0},{0,1,0},{0,0,1}}};
    }
};

constexpr double PI() {
    return 4*atan(1);
}


struct nd {
    // self, left self right, right self left
    Matrix mat[3];
    bool rev;
    nd *p, *ch[2];
    nd():mat{},rev(0),p(0),ch{0}{}
} *lct[MN];

inline Matrix getM(nd *n, int i) {
    return n?n->mat[i]:Matrix::id();
}

inline bool par(nd *n) {
    return n->p&&(n->p->ch[0]==n||n->p->ch[1]==n);
}

inline void psh(nd *n) {
    if(!n) return;
    if(n->rev) {
        std::swap(n->ch[0], n->ch[1]);
        std::swap(n->mat[1], n->mat[2]);
        if(n->ch[0]) n->ch[0]->rev^=1;
        if(n->ch[1]) n->ch[1]->rev^=1;
        n->rev=0;
    }
}

inline void upd(nd *n) {
    psh(n->ch[0]), psh(n->ch[1]);
    n->mat[1] = getM(n->ch[0], 1) * n->mat[0] * getM(n->ch[1], 1);
    n->mat[2] = getM(n->ch[1], 2) * n->mat[0] * getM(n->ch[0], 2);
}

inline Matrix getRot(double theta) {
    Matrix m;
    m(0, 0) = cos(theta * PI() / 180);
    m(0, 1) = -sin(theta * PI() / 180);
    m(1, 0) = sin(theta * PI() / 180);
    m(1, 1) = cos(theta * PI() / 180);
    m(2, 2) = 1;
    return m;
}

inline Matrix getTrans(double x, double y) {
    Matrix m;
    m(0, 0) = 1;
    m(0, 2) = x;
    m(1, 1) = 1;
    m(1, 2) = y;
    m(2, 2) = 1;
    return m;
}

inline Matrix getMove(double x, double y, double P) {
    Matrix m;
    m(0, 0) = P/100;
    m(0, 2) = (1 - P/100) * x;
    m(1, 1) = P/100;
    m(1, 2) = (1 - P/100) * y;
    m(2, 2) = 1;
    return m;
}

inline void rot(nd *n, bool b) {
    nd *p=n->p;
    if(p->ch[!b] = n->ch[b]) n->ch[b]->p=p;
    if(n->p=p->p) {
        if(p->p->ch[0]==p) n->p->ch[0]=n;
        if(p->p->ch[1]==p) n->p->ch[1]=n;
    }
    p->p=n;
    n->ch[b]=p;
    psh(p);
    upd(p);
}

inline void splay(nd *n) {
    while(par(n)) {
        bool p=par(n->p);
        if(p) psh(n->p->p);
        psh(n->p), psh(n);
        if(p) {
            bool b = n->p->p->ch[0]==n->p;
            if(n->p->ch[b]==n) rot(n, !b), rot(n, b);
            else rot(n->p, b), rot(n, b);
        } else rot(n, n->p->ch[0]==n);
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

inline void lnk(nd *u, nd *v) {
    evert(u);
    u->p=v;
}

int N, M;
int main() {
    scanf("%d%d", &N, &M);
    for(int i=1;i<=N;++i) {
        lct[i] = new nd();
        char op;
        double d1,d2,d3;
        scanf(" %c", &op);
        if(op == 'R') {
            scanf("%lf",&d1);
            lct[i]->mat[0] = getRot(d1);
        } else if(op == 'T') {
            scanf("%lf%lf",&d1,&d2);
            lct[i]->mat[0] = getTrans(d1, d2);
        } else {
            scanf("%lf%lf%lf",&d1,&d2,&d3);
            lct[i]->mat[0] = getMove(d1, d2, d3);
        }
        upd(lct[i]);
    }
    for(int i=1,a,b;i<N;++i) {
        scanf("%d%d",&a,&b);
        lnk(lct[a], lct[b]);
    }
    for(int i=0;i<M;++i) {
        char op;
        int a,b;
        double d1,d2,d3;
        scanf(" %c", &op);
        if(op == 'Q') {
            scanf("%d%d%lf%lf",&a,&b,&d1,&d2);
            evert(lct[a]); access(lct[b]);
            Matrix ret = Matrix{{{d1, 0, 0}, {d2, 0, 0}, {1, 0, 0}}};
            ret = lct[b]->mat[2] * ret;
            printf("%lf %lf\n", ret(0, 0), ret(1, 0));
        } else {
            scanf("%d %c", &a, &op);
            splay(lct[a]);
            if(op == 'R') {
                scanf("%lf",&d1);
                lct[a]->mat[0] = getRot(d1);
            } else if(op == 'T') {
                scanf("%lf%lf",&d1,&d2);
                lct[a]->mat[0] = getTrans(d1, d2);
            } else {
                scanf("%lf%lf%lf",&d1,&d2,&d3);
                lct[a]->mat[0] = getMove(d1, d2, d3);
            }
            upd(lct[a]);
        }
    }
}
