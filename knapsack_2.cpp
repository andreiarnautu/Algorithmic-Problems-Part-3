/**
  *  Worg
  */
#include <vector>
#include <iostream>

int main() {
	int n, w; std::cin >> n >> w;
//	dp[i] = cel mai mic weight care da valoarea i
//  initializam dp[0] = 0, in rest dp[i] = w + 1

	std::vector<int> dp(1 + n * 1000, w + 1);
	dp[0] = 0;

	for (int i = 0; i < n; i++) {
		int weight, value; std::cin >> weight >> value;

		for (int j = n * 1000 - value; j >= 0; j--) {
			if (dp[j] + weight <= w) {
				dp[j + value] = std::min(dp[j + value], dp[j] + weight);
			}
		}
	}

	for (int i = n * 1000; i >= 0; i--) {
		if (dp[i] <= w) {
			std::cout << i << "\n"; return 0;
		}
	}
}
