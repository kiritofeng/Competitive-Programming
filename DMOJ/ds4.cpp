#include <bits/stdc++.h>

using namespace std;

struct node {
    int val, sz, p;
    node *l, *r;
    
    int rand32() {
        return rand() & 0xffff << 15 | rand() & 0xffff;
    }
    
    node(int i) : val(i), sz(1), p(rand32()){
        l = 0;
        r = 0;
    }

    ~node() {
        free(l);
        free(r);
    }
};

int sz(node* n) {
    return n ? n-> sz : 0;
}

void upd_sz(node* &n) {
    if(n)
        n -> sz = sz(n -> l) + sz(n -> r) + 1;
}

void split(node* n, node* &l, node* &r, int key) {
    if(!n) l = r = NULL;
    else if(n -> val <= key) split(n -> r, n -> r, r, key), l = n;
    else split(n -> l, l, n -> l, key), r = n;
    upd_sz(n);
}

void merge(node* &n, node* l, node* r) {
    if(!l || !r) n = l ? l : r;
    else if (l -> p > r-> p) merge(l -> r, l -> r, r), n = l;
    else merge(r -> l, l, r-> l), n = r;
    upd_sz(n);
}

void insert(node* &n, node* i) {
    if(!n) n = i;
    else if(i -> p > n -> p) split(n, i -> l, i-> r, i-> val), n = i;
    else insert(n -> val <= i -> val? n -> r: n -> l, i);
    upd_sz(n);
}

void erase(node* &n, int val) {
    if(!n) return;
    else if(n -> val == val) {
        node* tmp = n;
        merge(n, n-> l, n-> r);
        free(tmp);
    } else erase(n -> val < val ? n -> r:  n-> l, val);
    upd_sz(n);
}

int rnk(node* n, int val, int ind = 0) {
    if(!n) return -1;
    if(n -> val == val) {
        int oth = rnk(n -> l, val, ind);
        if(~oth) return oth;
        else return ind + sz(n -> l) + 1;
    }
    if(n -> val < val) return rnk(n -> r, val, ind + sz(n -> l) + 1);
    else return rnk(n -> l, val, ind);
}

int select(node* n, int rnk) {
    if(!n) return -1;
    int lsz = sz(n -> l) + 1;
    if(lsz == rnk) return n -> val;
    else if(lsz < rnk) return select(n -> r, rnk - lsz);
    else return select(n -> l, rnk);
}

void traverse(node* n) {
    if(!n) return;
    traverse(n -> l);
    printf("%d ", n -> val);
    traverse(n -> r);
}

int N, M, ans;
node * root = 0;
int main() {
    scanf("%d%d", &N, &M);
    for(int i=0, a;i<N;i++) {
        scanf("%d", &a);
        insert(root, new node(a));
    }
    char c;
    for(int i=0, j;i<M;i++) {
        scanf(" %c%d", &c, &j);
        j ^= ans;
        switch(c) {
            case 'I':
                insert(root, new node(j));
                break;
            case 'R':
                erase(root, j);
                break;
            case 'S':
                printf("%d\n", ans = select(root, j));
                break;
            case 'L':
                printf("%d\n", ans = rnk(root, j));
        }
    }
    traverse(root);
}
