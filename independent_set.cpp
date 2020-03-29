/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MOD = 1e9 + 7;

void dfs(int node, int father, std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& dp) {
    // 0 = white, 1 = black
    dp[node][0] = dp[node][1] = 1;
    for (auto& son: graph[node]) {
        if (son != father) {
            dfs(son, node, graph, dp);
            dp[node][0] = 1LL * dp[node][0] * (dp[son][0] + dp[son][1]) % MOD;
            dp[node][1] = 1LL * dp[node][1] * dp[son][0] % MOD;
        }
    }
}


int main() {
    int n; std::cin >> n;
    std::vector<std::vector<int>> graph(n);

    for (int i = 1; i < n; i++) {
        int u, v; std::cin >> u >> v;
        u--; v--;
        graph[u].push_back(v); graph[v].push_back(u);
    }

    std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
    dfs(0, 0, graph, dp);
    std::cout << (dp[0][0] + dp[0][1]) % MOD << "\n";
    return 0;
}
