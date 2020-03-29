/**
  *  Worg
  */
#include <vector>
#include <iostream>

int main() {
	int n; std::cin >> n;
	std::vector<std::vector<int>> add(n, std::vector<int>(3));
	for (int i = 0; i < n; i++) {
		std::cin >> add[i][0] >> add[i][1] >> add[i][2];
	}

	std::vector<std::vector<int>> dp(n, std::vector<int>(3, 0));
	dp[0][0] = add[0][0]; dp[0][1] = add[0][1]; dp[0][2] = add[0][2];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (j != k) {
					dp[i][j] = std::max(dp[i][j], dp[i - 1][k] + add[i][j]);
				}
			}
		}
	}

	std::cout << std::max(dp[n - 1][0], std::max(dp[n - 1][1], dp[n - 1][2])) << '\n';
	return 0;
}
