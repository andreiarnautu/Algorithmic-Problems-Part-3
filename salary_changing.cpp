/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_VALUE = 1e9;

int solve_test() {
    int n; std::cin >> n;
    long long s; std::cin >> s;

    std::vector<std::pair<int, int>> v(n);
    for (auto& p: v) {
        std::cin >> p.first >> p.second;
        s -= p.first;
    }

    std::sort(v.begin(), v.end());

    int left = 1, right = MAX_VALUE, answer = 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        int needed = n / 2 + 1;
        long long cash = s;
        for (int i = n - 1; i >= 0; i--) {
            if (v[i].first >= mid) {
                needed -= 1;
            } else if (mid <= v[i].second) {
                cash -= (mid - v[i].first);
                if (cash >= 0) {
                    needed -= 1;
                }
            }
        }

        if (needed <= 0) {
            answer = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return answer;
}

int main() {
    int test_count; std::cin >> test_count;

    for (int i = 0; i < test_count; i++) {
        std::cout << solve_test() << "\n";
    }
}
