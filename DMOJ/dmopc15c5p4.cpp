#include <bits/stdc++.h>

using namespace std;

string S, E, K, T;
int Q;
set<string>SS;
int main() {
    ios::sync_with_stdio(0);
    K = "HAILHYDRA";
    cin >> S;
    for(int i=0;i<S.length() - 9; i++)
        SS.insert(S.substr(i, 9));
    cin >> Q;
    for(int i=0;i<Q;i++) {
        cin >> E;
        T = "";
        for(char c: K)
            T += E[c - 'A'];
        if(SS.find(T) != SS.end()) {
            T = "";
            for(int i=0;i<26;i++)
                T[E[i] - 'A'] = i + 'A';
            for(char cc:S)
                cout << T[cc - 'A'];
            return 0;
        }
    }
    cout << "KeyNotFoundError";
}
