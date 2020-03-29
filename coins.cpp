/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

int main() {
	int n; std::cin >> n;
	std::vector<double> p(n);
	for (auto& x: p) {
		std::cin >> x;
	}

	std::vector<std::vector<double>> dp(n, std::vector<double>(n + 1, 0));
	dp[0][0] = 1 - p[0]; dp[0][1] = p[0];

	for (int i = 1; i < n; i++) {
		dp[i][0] = dp[i - 1][0] * (1 - p[i]);
		for (int j = 1; j <= i + 1; j++) {
			dp[i][j] = dp[i - 1][j - 1] * p[i] + dp[i - 1][j] * (1 - p[i]);
		}
	}

	double answer = 0;
	for (int i = 0; i <= n; i++) {
		if (i > n - i) {
			answer += dp[n - 1][i];
		}
	}

	std::cout << std::fixed << std::setprecision(10) << answer << "\n";
	return 0;
}
