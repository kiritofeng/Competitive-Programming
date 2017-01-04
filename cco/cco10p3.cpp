#include <cstdio>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 16384, stdin)] = 0, *_pbuf++))
char _buf[16385], *_pbuf = _buf;

using namespace std;
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> bbst;


static inline int read() {
    int c, o = 0;
    while ((c = getchar()) < '0');
    do o = (o << 1) + (o << 3) + c - '0';
    while ((c = getchar()) >= '0');
    return o;
}

int N, a, b, tmp, rnk[1000004];
char c;
unordered_map<int, int>player;
bbst lul;
int main() {
    N = read();
    for(int i=0;i<N;i++) {
        c = getchar();
        switch(c) {
            case 'N':
                a = read();
                b = read();
                rnk[a] = b;
                player[b] = a;
                lul.insert({b, i});
                break;
            case 'M':
                a = read();
                b = read();
                lul.erase(lul.lower_bound({rnk[a], 0}));
                player[rnk[a]] = 0;
                rnk[a] = b;
                player[b] = a;
                lul.insert({b, i});
                break;
            case 'Q':
                a = read();
                printf("%d\n", player[lul.find_by_order(lul.size() - a) -> first]);
                break;
        }
    }
}
