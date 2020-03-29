/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MOD = 1e9 + 7;

void fix(int& value) {
	if (value >= MOD) {
		value -= MOD;
	}
}

int main() {
	int n, m; std::cin >> n >> m;
	std::vector<std::vector<char>> a(n, std::vector<char>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >> a[i][j];
		}
	}

	std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (a[i][j] == '#') {
				dp[i][j] = 0; continue;
			}

			if (i == 0 && j == 0) {
				dp[i][j] = 1;
			} else if (i == 0) {
				dp[i][j] = dp[i][j - 1];
			} else if (j == 0) {
				dp[i][j] = dp[i - 1][j];
			} else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
				fix(dp[i][j]);
			}
		}
	}

	std::cout << dp[n - 1][m - 1] << "\n";
	return 0;
}

