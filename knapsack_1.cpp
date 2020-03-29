/**
  *  Worg
  */
#include <vector>
#include <iostream>

int main() {
	int n, w; std::cin >> n >> w;
	std::vector<long long> dp(w + 1, -1);
	dp[0] = 0;

	for (int i = 0; i < n; i++) {
		int weight, value; std::cin >> weight >> value;

		for (int j = w - weight; j >= 0; j--) {
			if (dp[j] != -1) {
				dp[j + weight] = std::max(dp[j + weight], dp[j] + value);
			}
		}
	}

	long long answer = 0;
	for (auto& value: dp) {
		answer = std::max(answer, value);
	}
	std::cout << answer << '\n';

	return 0;
}
