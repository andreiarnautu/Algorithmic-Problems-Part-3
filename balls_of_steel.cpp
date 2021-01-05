/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

bool close(std::pair<int, int> a, std::pair<int, int> b, int k) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second) <= k;
}

int main() {
    int tests; std::cin >> tests;
    for (int test = 0; test < tests; test++) {
        int n, k; std::cin >> n >> k;

        std::vector<std::pair<int, int>> points(n);
        for (auto& point : points) {
            std::cin >> point.first >> point.second;
        }

        int answer = -1;
        for (int i = 0; i < n; i++) {
            bool is_center = true;
            for (int j = 0; j < n; j++) {
                if (!close(points[i], points[j], k)) {
                    is_center = false; break;
                }
            }
            if (is_center) {
                answer = 1;
            }
        }

        std::cout << answer << '\n';
    }
    return 0;
}
