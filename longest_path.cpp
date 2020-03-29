/**
  *  Worg
  */
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	int n, m; std::cin >> n >> m;
	std::vector<std::vector<int>> graph(n);
	std::vector<int> degree(n, 0), dp(n, 0);

	for (int i = 0; i < m; i++) {
		int u, v; std::cin >> u >> v;
		u--; v--;
		graph[u].push_back(v);
		degree[v] += 1;
	}

	std::queue<int> q;
	for (int i = 0; i < n; i++) {
		if (!degree[i]) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int node = q.front(); q.pop();

		for (auto& x: graph[node]) {
			degree[x] -= 1;
			dp[x] = std::max(dp[x], dp[node] + 1);

			if (degree[x] == 0) {
				q.push(x);
			}
		}
	}

	int answer = 0;
	for (int i = 0; i < n; i++) {
		answer = std::max(answer, dp[i]);
	}
	std::cout << answer << "\n";
	return 0;
}
