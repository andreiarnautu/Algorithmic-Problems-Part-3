/**
  *  Worg
  */
#include <vector>
#include <iostream>

int main() {
    int n, m, k; std::cin >> n >> m >> k;

    std::vector<std::vector<char>> a(n, std::vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::vector<std::vector<int>> dp_left(n, std::vector<int>(m, 0)), dp_up(n, std::vector<int>(m, 0));

    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i != 0) {
                dp_up[i][j] = dp_up[i - 1][j];
            }
            if (j != 0) {
                dp_left[i][j] = dp_left[i][j - 1];
            }

            if (a[i][j] == '.') {
                dp_up[i][j] += 1;
                dp_left[i][j] += 1;
            } else {
                dp_up[i][j] = dp_left[i][j] = 0;
            }

            if (dp_up[i][j] >= k) {
                answer++;
            }
            if (dp_left[i][j] >= k) {
                answer++;
            }

            if (dp_up[i][j] >= 1 && dp_left[i][j] >= 1 && k == 1) {
                answer--;
            }
        }
    }
    std::cout << answer << '\n';

    return 0;
}
