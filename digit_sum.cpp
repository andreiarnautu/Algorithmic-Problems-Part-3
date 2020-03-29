/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

const int mod = 1e9 + 7;

void fix(int& value) {
	if (value >= mod) {
		value -= mod;
	}
}

int main() {
	std::string k; std::cin >> k;
	int d; std::cin >> d;

	std::vector<std::vector<int>> dp(d, std::vector<int>(2, 0));
	dp[0][0] = 1;

	for (int i = 0; i < (int)k.size(); i++) {
		std::vector<std::vector<int>> new_dp(d, std::vector<int>(2, 0));

		for (int sum = 0; sum < d; sum++) {
			for (int digit = 0; digit < 10; digit++) {
				for (int smaller = 0; smaller < 2; smaller++) {
					if (digit > k[i] - '0' && !smaller) continue;

					new_dp[(sum + digit) % d][smaller || (digit < k[i] - '0')] += dp[sum][smaller];
					fix(new_dp[(sum + digit) % d][smaller || (digit < k[i] - '0')]);
				}
			}
		}
		dp = new_dp;
	}
	int answer = (dp[0][0] + dp[0][1]) % mod;
	answer = (answer - 1 + mod) % mod;
	std::cout << answer << "\n";
	return 0;
}
