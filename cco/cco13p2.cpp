#include <bits/stdc++.h>
#define LEFT ind << 1
#define RIGHT ind << 1 | 1

using namespace std;

typedef long long ll;


struct segment{
    int l, r, w;
}seg[1 << 21];

int data[1 << 21];

int N, M, comp, sk, won[1 << 21];

int winner(int a, int b) {
    return data[a]>data[b]?a:b;
}

void build(int ind, int left, int right) {
    seg[ind].l = left;
    seg[ind].r = right;
    if(left ^ right) {
        int mid = (left + right) >> 1;
        build(LEFT, left, mid);
        build(RIGHT, mid + 1, right);
        seg[ind].w = winner(seg[LEFT].w, seg[RIGHT].w);
        won[seg[ind].w]++;
    } else {
        seg[ind].w = left;
    }
}

void update(int ind, int uid) {
    int left = seg[ind].l, right = seg[ind].r, mid = (left + right) >> 1;
    if(left^right) {
        if(uid <= mid) {
            update(LEFT, uid);
        }else if(uid > mid) {
            update(RIGHT, uid);
        }
        won[seg[ind].w]--;
        seg[ind].w = winner(seg[LEFT].w, seg[RIGHT].w);
        won[seg[ind].w]++;
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= (1 << N); i ++) {
        scanf("%d", &data[i]);
    }
    build(1, 1, (1 << N));
    char cmd;
    for(int i = 0; i < M; i ++) {
        scanf(" %c", &cmd);
        switch(cmd) {
            case 'R':
                scanf("%d%d", &comp, &sk);
                data[comp] = sk;
                update(1, comp);
                break;
            case 'W':
                printf("%d\n", seg[1].w);
                break;
            case 'S':
                scanf("%d", &comp);
                printf("%d\n", won[comp]);
                break;
        }
    }
    return 0;
}
