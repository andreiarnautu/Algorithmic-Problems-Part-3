/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const long long INF = 1e18;

int main() {
    int n; std::cin >> n;
    std::vector<long long> sum_a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long x; std::cin >> x;
        sum_a[i] = sum_a[i - 1] + x;
    }

    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(n + 1, INF));
    for (int i = n; i >= 1; i--) {
        dp[i][i] = 0;
        for (int j = i + 1; j <= n; j++) {
            for (int k = i; k < j; k++) {
                long long current_cost = dp[i][k] + dp[k + 1][j] + sum_a[j] - sum_a[i - 1];
                dp[i][j] = std::min(dp[i][j], current_cost);
            }
        }
    }

    std::cout << dp[1][n] << "\n";
    return 0;
}
