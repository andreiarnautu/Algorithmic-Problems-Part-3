/**
  *  Worg
  */
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>

const int INF = 1e9;

int main() {
	int n; std::cin >> n;
	std::vector<int> h(n);
	for (auto& x : h) {
		std::cin >> x;
	}

	std::vector<int> dp(n, INF);
	dp[0] = 0;

	for (int i = 1; i < n; i++) {
		dp[i] = std::min(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));

		if (i > 1) {
			dp[i] = std::min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
		}
	}

	std::cout << dp.back() << '\n';
	return 0;
}
