#include <bits/stdc++.h>

using namespace std;

//Screw ropes
//Persistant array FTW

const int MAXQ = 1000004;

struct node {
    char val;
    node *l, *r;

    node(): val(0), l(0), r(0){};

    node(char c): val(c), l(0), r(0){};

    node(node* n): val(n -> val), l(n -> l), r(n -> r){};

    node(char c, node* n): val(c), l(n -> l), r(n -> r){};
}*N[MAXQ];

int Q, L, last[MAXQ];
char c;

void build(node* &n, int l, int r) {
    if(l <= r) {
        n = new node();
        int mid = l + r >> 1;
        build(n -> l, l, mid - 1);
        build(n -> r, mid + 1, r);
    }
}

void insert(node* &n, node* old, char val, int pos, int l, int r) {
    int mid = l + r >> 1;
    if(pos == mid) {
        n = new node(val, old);
    } else if(pos < mid) {
        n = new node(old);
        insert(n -> l, old -> l, val, pos, l, mid - 1);
    } else {
        n = new node(old);
        insert(n -> r, old -> r, val, pos, mid + 1, r);
    }
}

char report(node* n, int pos, int l, int r) {
    int mid = l + r >> 1;
    if(pos == mid)
        return n -> val;
    else if(pos < mid)
        return report(n -> l, pos, l, mid - 1);
    else
        return report(n -> r, pos, mid + 1, r);
}

int main() {
    scanf("%d", &Q);
    build(N[0], 0, Q - 1);
    last[0] = -1;
    for(int i=1, ind = 1, j;i<=Q;++i) {
        scanf(" %c", &c);
        switch(c) {
            case 'T':
                scanf(" %c", &c);
                insert(N[ind], N[ind - 1], c, last[ind] = last[ind - 1] + 1, 0, Q - 1);
                ++ind;
                break;
            case 'U':
                scanf("%d", &j);
                N[ind] = N[ind - j - 1];
                last[ind] = last[ind - j - 1];
                ++ind;
                break;
            case 'P':
                scanf("%d", &j);
                printf("%c\n", report(N[ind-1], j, 0, Q - 1));
                break;
        }
    }
    return 0;
}
