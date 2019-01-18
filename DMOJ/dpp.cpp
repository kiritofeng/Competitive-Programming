#include<bits/stdc++.h>
typedef long long ll;
const int MOD=1e9+7,MN=1e5+4;
int N;
ll dp[MN][2];
std::vector<int>adj[MN];
inline void dfs(int src,int pre) {
	dp[src][0] = dp[src][1] = 1;
	for(int i:adj[src]) {
		if(i == pre) continue;
		dfs(i, src);
		dp[src][0] = (dp[src][0] * (dp[i][0] + dp[i][1])) % MOD;
		dp[src][1] = (dp[src][1] * dp[i][0]) % MOD;
	}
}
int main() {
	scanf("%d",&N);
	for(int i=1,a,b;i<N;++i) {
		scanf("%d%d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1,0);
	printf("%lld\n",(dp[1][0]+dp[1][1])%MOD);
}
