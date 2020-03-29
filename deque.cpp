/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const long long INF = 1e13;

int main() {
	int n; std::cin >> n;
	std::vector<int> a(n);
	for (auto& x: a) {
		std::cin >> x;
	}

	int parity = n % 2;

	std::vector<std::vector<long long>> dp(n, std::vector<long long>(n));
	for (int i = n - 1; i >= 0; i--) {
		if (parity == 0) {
			dp[i][i] = -a[i];
		} else {
			dp[i][i] = a[i];
		}

		for (int j = i + 1; j < n; j++) {
			int curr_parity = (j - i + 1) % 2;

			//  Compute accordingly
			if (curr_parity == parity) {
				dp[i][j] = std::max(a[i] + dp[i + 1][j], a[j] + dp[i][j - 1]);
			} else {
				dp[i][j] = std::min(-a[i] + dp[i + 1][j], -a[j] + dp[i][j - 1]);
			}
		}
	}
	std::cout << dp[0][n - 1] << "\n";
	return 0;
}
