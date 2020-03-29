/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("caibicol.in"); std::ofstream fout("caibicol.out");

const int INF = 1e9;

int main() {
    int n, k; fin >> n >> k;

    std::vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> color[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, INF));
    dp[0][0] = 0;

    std::vector<int> count(2);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (dp[i][j] == INF || i == n || j == k) continue;

            count[0] = count[1] = 0;
            for (int it = i + 1; it <= n; it++) {
                count[color[it]] += 1;
                dp[it][j + 1] = std::min(dp[it][j + 1], dp[i][j] + count[0] * count[1]);
            }
        }
    }

    fout << dp[n][k] << "\n";
    return 0;
}
