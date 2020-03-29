/**
  *  Worg
  */
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

int main(int argc, char const *argv[]) {
    int n; std::cin >> n;
    std::vector<int> vec(n);
    for (auto& num : vec) {
        std::cin >> num;
    }

    if (n <= 2) {
        std::cout << "0\n"; return 0;
    }

    int ans = n + 1;
    for (int p1 = vec[0] - 1; p1 <= vec[0] + 1; p1++) {
        for (int p2 = vec[1] - 1; p2 <= vec[1] + 1; p2++) {
            int cnt = (p1 != vec[0]) + (p2 != vec[1]);
            int dif = p2 - p1;

            for (int i = 2; i < n; i++) {
                long long num = 1LL * p1 + 1LL * i * dif;

                if (std::abs(num - 1LL * vec[i]) > 1) {
                    cnt = n + 1; break;
                }

                cnt += (num != vec[i]);
            }

            ans = std::min(ans, cnt);
        }
    }

    if (ans == n + 1) {
        std::cout << "-1\n";
    } else {
        std::cout << ans << '\n';
    }
    return 0;
}
