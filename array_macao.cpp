/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_N = 1e5 + 5;

int n;
int a[2][MAX_N];
int dp[2][MAX_N][10];

std::vector<int> get_digits(int x) {
    std::vector<int> ans;

    while (x != 0) {
        ans.push_back(x % 10);
        x /= 10;
    }

    return ans;
}

int main() {
    int n; std::cin >> n;
    for (int id = 0; id < 2; id++) {
         for (int i = 1; i <= n; i++) {
            std::cin >> a[id][i];
        }
    }

    // dp[0/1][i][digit] = cel mai lung sir in care {Alice/Bob} incepe, prima carte are indice >= {i} si are in componenta cifra {digit}
    for (int i = n; i >= 1; i--) {
        for (int id = 0; id < 2; id++) {
            std::vector<int> digits = get_digits(a[id][i]);

            for (auto& d1: digits) {
                for (auto& d2: digits) {
                    dp[id][i][d1] = std::max(dp[id][i][d1], 1 + dp[id ^ 1][i + 1][d2]);
                }
            }
            for (int d = 0; d < 10; d++) {
                dp[id][i][d] = std::max(dp[id][i][d], dp[id][i + 1][d]);
            }
        }
    }

    int ans = 0;
    for (int d = 0; d < 10; d++) {
        ans = std::max(ans, dp[0][1][d]);
    }
    std::cout << ans << "\n";
    return 0;
}
