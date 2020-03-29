/**
  *  Worg
  */
#include <string>
#include <iostream>
#include <algorithm>

const int MAX_N = 200000 + 1;

int dp[MAX_N][2][2][2];
char prev[MAX_N][2][2][2];
char candidates[5];

std::string a, b, c;

int main(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin >> a >> b >> c;
    int n = (int)a.size();

    dp[0][1][1][1] = 1;

    for (int i = 0; i < n; i++) {
        for (int na = 0; na <= 1; na++) {
            for (int nb = 0; nb <= 1; nb++) {
                for (int nc = 0; nc <= 1; nc++) {
                    if (dp[i][na][nb][nc] == 0) continue;

                    if (dp[i][na][nb][nc] > 2) {
                        dp[i][na][nb][nc] = 2;
                    }

                    int count = 0;
                    candidates[count++] = a[i];
                    if (b[i] != a[i]) {
                        candidates[count++] = b[i];
                    }
                    if (c[i] != a[i] && c[i] != b[i]) {
                        candidates[count++] = c[i];
                    }

                    for (int ch = 'a'; ch <= 'z' && count < 5; ch++) {
                        if (ch != a[i] && ch != b[i] && ch != c[i]) {
                            candidates[count++] = ch;
                        }
                    }

                    for(int it = 0; it < count; it++) {
                        char ch = candidates[it];

                        int _na = na, _nb = nb, _nc = nc;
                        if (ch != a[i]) {
                            _na -= 1;
                        }
                        if (ch != b[i]) {
                            _nb -= 1;
                        }
                        if (ch != c[i]) {
                            _nc -= 1;
                        }

                        if (_na >= 0 && _nb >= 0 && _nc >= 0) {
                            dp[i + 1][_na][_nb][_nc] += dp[i][na][nb][nc];
                            prev[i + 1][_na][_nb][_nc] = ch;
                        }
                    }
                }
            }
        }
    }

    int count_sol = 0, _na, _nb, _nc;
    for (int na = 0; na <= 1; na++) {
        for (int nb = 0; nb <= 1; nb++) {
            for (int nc = 0; nc <= 1; nc++) {
                count_sol += dp[n][na][nb][nc];

                if (dp[n][na][nb][nc] != 0) {
                    _na = na; _nb = nb; _nc = nc;
                }
            }
        }
    }

    if (count_sol == 0) {
        std::cout << "Impossible\n";
    } else if (count_sol > 1) {
        std::cout << "Ambiguous\n";
    } else {
        std::string result;

        for (int i = n; i > 0; i--) {
            char ch = prev[i][_na][_nb][_nc];

            result += ch;

            if (ch != a[i - 1]) {
                _na++;
            }
            if (ch != b[i - 1]) {
                _nb++;
            }
            if (ch != c[i - 1]) {
                _nc++;
            }
        }

        std::reverse(result.begin(), result.end());
        std::cout << result << '\n';
    }
    return 0;
}