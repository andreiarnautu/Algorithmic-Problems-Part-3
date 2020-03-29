/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("sunmihai.in"); std::ofstream fout("sunmihai.out");

const int INF = 1e9;
const int MAX_VAL = 100 + 1;

int main(int argc, char** argv) {
    int n, a, b, c; fin >> n >> a >> b >> c;
    std::vector<std::vector<int>> dp(2, std::vector<int>(MAX_VAL, INF));

    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;

        if (i == 0) {
            dp[1][x] = a;
            dp[1][y] = 0;
        } else {
            if (i < n - 1) {
                for (int j = 1; j < MAX_VAL; j++) {
                    dp[1][j] = dp[0][j] + b;  //  delete the current piece
                }
            } else {
                for (int j = 1; j < MAX_VAL; j++) {
                    dp[1][j] = INF;
                }
            }

            dp[1][y] = std::min(dp[1][y], dp[0][x]);
            dp[1][x] = std::min(dp[1][x], dp[0][y] + a);
        }

        int min_value = INF;
        for (int j = 1; j < MAX_VAL; j++) {
            min_value = std::min(min_value, dp[1][j]);
        }
        for (int j = 1; j < MAX_VAL; j++) {
            dp[1][j] = std::min(dp[1][j], min_value + c);
        }

        dp[0] = dp[1];
    }

    int answer = INF;
    for (int i = 1; i < MAX_VAL; i++) {
        answer = std::min(answer, dp[0][i]);
    }
    fout << answer << "\n";
    return 0;
}
