#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int Q, x;
char c;
deque<pii>L;
unordered_map<int, int>A;
int main() {
    scanf("%d", &Q);
    for(int i=1;i<=Q;i++) {
        scanf(" %c%d", &c, &x);
        switch(c) {
            case 'F':
                L.push_front({x, i});
                A[x] = i;
                break;
            case 'E':
                L.push_back({x, i});
                A[x] = i;
                break;
            case 'R':
                A[x] = 0;
        }
    }
    for(auto it = L.begin();it != L.end(); it++)
        if(A[it -> first] == (it -> second))
            printf("%d\n", it -> first);
}
