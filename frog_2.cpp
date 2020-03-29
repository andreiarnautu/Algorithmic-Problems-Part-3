/**
  *  Worg
  */
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>

const int INF = 1e9;

int main() {
	int n, k; std::cin >> n >> k;
	std::vector<int> h(n);
	for (auto& x : h) {
		std::cin >> x;
	}

	std::vector<int> dp(n, INF);
	dp[0] = 0;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= k && i - j >= 0; j++) {
			dp[i] = std::min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
		}
	}

	std::cout << dp.back() << '\n';
	return 0;
}
