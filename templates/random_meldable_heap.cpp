#include <bits/stdc++.h>

using namespace std;

struct node {
    int val;
    node *l,*r;

    node(int i) : val(i), l(0), r(0) {}
} *root = 0;

node* meld(node* n1, node* n2) {
    if(!n1 || !n2) return n1 ? n1 : n2;
    if(n1 -> val > n2 -> val) swap(n1, n2);
    if(rand() & 1) n1 -> r = meld(n1 -> r, n2);
    else n1 -> l = meld(n1 -> l, n2);
    return n1;
}

node* insert(int val) {
    return meld(root, new node(val));
}

node* pop() {
    return meld(root -> l, root -> r);
}

int top() {
    return root -> val;
}

int main() {
    root = insert(5);
    root = insert(6);
    root = insert(4);
    assert(top() == 4);
    root = pop();
    assert(top() == 5);
    root = insert(1);
    assert(top() == 1);
}
