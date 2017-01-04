#include <stdio.h>

typedef long long ll;

int cmd, S, a, b, c, d;
int tree[1024][1024];

inline void update(int x , int y , int val){
    int y1;
    while (x <= S){
        y1 = y;
        while (y1 <= S){
            tree[x][y1] += val;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

inline ll sum(int x, int y) {
    ll sum = 0;
    int y1;
    while(x > 0) {
        y1 = y;
        while(y1 > 0) {
            sum += tree[x][y1];
            y1 -= (y1 & -y1);
        }
        x-= (x & -x);
    }
    return sum;
}

int main() {
    do
    {
        scanf("%d", &cmd);
        switch(cmd) {
            case 0:
                scanf("%d", &S);
                break;
            case 1:
                scanf("%d %d %d", &a, &b, &c);
                update(a+1, b+1, c);
                break;
            case 2:
                scanf("%d %d %d %d", &a, &b, &c, &d);
                printf("%lld\n", sum(c+1, d+1)-sum(c+1, b)-sum(a, d+1)+sum(a, b));
                break;
        }
    }while(cmd != 3);

}
