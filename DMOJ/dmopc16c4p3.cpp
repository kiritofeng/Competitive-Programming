#include<bits/stdc++.h>

using namespace std;

/**
 * Operations:
 * A x k: The store x now sells candy apple k
 * S x k: The store x no longer sells candy apple k
 * E x k: The store x no longer sells any candy apples, and is now dist k
 * Q k: Query
 */

typedef pair<int, int> pii;

int N, S, Q, dist[100004];
set<pii>s[104];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> S;
    for(int i=1;i<=N;i++)
        cin >> dist[i];
    for(int i=0, a, b;i<S;i++) {
        cin >> a >> b;
        s[b].insert({dist[a], a});
    }
    cin >> Q;
    for(int i=0, b, c;i<Q;i++) {
        char a;
        cin >> a;
        //cerr << a;
        if (a == 'Q') {
            cin >> b;
            if(!s[b].empty())
                printf("%d\n", s[b].begin() -> second);
            else
                printf("-1\n");
        } else {
            cin >> b >> c;
            if (a == 'A') {
                s[c].insert({dist[b], b});
            } else if (a == 'S') {
                auto it = s[c].find({dist[b], b});
                if(it != s[c].end())
                    s[c].erase(it);
            } else if (a == 'E') {
                for(int i=0;i<100;i++) {
                    auto it = s[i].find({dist[b], b});
                    if(it != s[i].end()) s[i].erase(it);
                }
                dist[b] = c;
            }
        }
    }
}
