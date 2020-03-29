/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	std::string s, t; std::cin >> s >> t;
	int n = (int)s.size(), m = (int)t.size();
	s.resize(n + 1); t.resize(m + 1);
	for (int i = n; i >= 1; i--) {
		s[i] = s[i - 1];
	}
	for (int j = m; j >= 1; j--) {
		t[j] = t[j - 1];
	}

	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

			int x = dp[i - 1][j - 1] + (s[i] == t[j]);
			dp[i][j] = std::max(dp[i][j], x);
		}
	}

	std::string result;
	int i = n, j = m;
	while (i > 0 && j > 0) {
		int x = dp[i - 1][j - 1] + (s[i] == t[j]);
		if (dp[i - 1][j] >= dp[i][j - 1] && dp[i - 1][j] >= x) {
			i -= 1;
		} else if (dp[i][j - 1] >= dp[i - 1][j] && dp[i][j - 1] >= x) {
			j -= 1;
		} else {
			if (s[i] == t[j]) {
				result += s[i];
			}
			i -= 1; j -= 1;
		}
	}

	std::reverse(result.begin(), result.end());
	std::cout << result << '\n';
	return 0;
}
