#include "bits/stdc++.h"
const int MP = 12;
int N, P, Q, lim[MP][MP];
std::pair<bool, std::vector<int>> solve(std::vector<int> &vec, int a, int b) {
    if(vec.empty()) {
        assert(0);
    }
    if(a == 1 || b == 1) {
        return {a == 1, {vec.back()}};
    }
    int cur = vec.back();
    vec.pop_back();
    std::string s;
    std::cout << "A " << cur << std::endl;
    std::cin >> s;
    std::vector<int> v0, v1;
    for(int i : vec) {
        if(s[i-1] == '1') v1.push_back(i);
        else v0.push_back(i);
    }
    if(v1.size() >= lim[a-1][b]) {
        auto ret = solve(v1, a-1, b);
        if(ret.first) {
            ret.second.push_back(cur);
            return ret;
        } else {
            return ret;
        }
    }
    if(v0.size() >= lim[a][b-1]) {
        auto ret = solve(v0, a, b-1);
        if(ret.first) {
            return ret;
        } else {
            ret.second.push_back(cur);
            return ret;
        }
    }
    assert(0);
}
int main() {
    std::cin >> N >> P >> Q;
    for(int i = 1; i <= P; ++i) {
        lim[i][1] = lim[1][i] = 1;
    }
    for(int i = 2; i <= P; ++i) {
        for(int j = 2; j <= P; ++j) {
            lim[i][j] = lim[i-1][j] + lim[i][j-1];
        }
    }
    std::vector<int> num;
    for(int i = 1; i <= N; ++i) {
        num.push_back(i);
    }
    auto ret = solve(num, P, P).second;
    std::cout << "C";
    for(int i : ret) {
        std::cout << " " << i;
    }
    std::cout << std::endl;
}
