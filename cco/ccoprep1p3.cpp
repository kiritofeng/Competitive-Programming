#include <bits/stdc++.h>

using namespace std;

struct node {
    int val, stu, sz, p;
    node* l, *r;

    node(int i, int j) : val(i), stu(j), sz(1), p(rand()), l(0), r(0){}
};

int sz(node * n) {
    return n ? n->sz : 0;
}

void upd_sz(node* &n) {
    if(n) n -> sz = sz(n -> l) + 1 + sz(n -> r);
}

void split(node* n, node* &l, node* &r, int key) {
    if(!n) l = r = 0;
    else if(n->val <= key) split(n -> r, n -> r, r, key), l = n;
    else split(n -> l, l, n->l, key), r = n;
    upd_sz(n);
}

void insert(node* &n, node* i) {
    if(!n) n = i;
    else if(i -> p > n -> p) split(n, i->l, i->r, i->val), n = i;
    else insert(n->val<=i->val ? n->r : n->l, i);
    upd_sz(n);
}

int rnk(node* n, int key) {
    if(!n) return -1;
    int lsz = sz(n -> l) + 1;
    if(key == lsz) return n->stu;
    else if(key < lsz) return rnk(n -> l, key);
    else return rnk(n -> r, key - lsz);
}

const int MAXN = 1000004;
int N, M, Q, ds[MAXN];
node* students[MAXN]={0};
char c;

void init() {
    for(int i=1;i<=N;i++) ds[i] = i;
}

int find(int x) {
    return ds[x] == x ? x : ds[x] = find(ds[x]);
}

void traverse(node *n, int i) {
    if(!n) return;
    traverse(n -> l, i);
    traverse(n -> r, i);
    insert(students[i], n);
}

void merge(int x, int y) {
    if((x = find(x)) != (y = find(y))) {
        traverse(students[x], y);
        ds[x] = y;
    }
}

int main() {
    scanf("%d%d", &N, &M);
    init();
    for(int i=1, a;i<=N;i++) {
        scanf("%d", &a);
        insert(students[i], new node(a, i));
    }
    for(int i=0, a, b;i<M;i++) {
        scanf("%d%d", &a, &b);
        merge(a, b);
    }
    scanf("%d", &Q);
    for(int i=0, a, b;i<Q;i++) {
        scanf(" %c%d%d", &c, &a, &b);
        if(c == 'Q')
            printf("%d\n", rnk(students[find(a)], b));
        else
            merge(a, b);
    }
}
