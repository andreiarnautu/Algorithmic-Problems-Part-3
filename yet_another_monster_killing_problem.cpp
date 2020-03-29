/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int solve_test() {
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (auto& x: a) {
        std::cin >> x;
    }

    int m; std::cin >> m;
    std::vector<int> biggest_power(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int p, s; std::cin >> p >> s;
        biggest_power[s] = std::max(biggest_power[s], p);
    }

    for (int i = n - 1; i >= 1; i--) {
        biggest_power[i] = std::max(biggest_power[i + 1], biggest_power[i]);
    }

    int id = 0, counter = 0;
    while (id < n) {
        int today = 0;
        for (int max_val = a[id]; id + today < n && biggest_power[today + 1] >= max_val; today++) {
            max_val = std::max(max_val, a[id + today + 1]);
        }
        if (today == 0) {
            return -1;
        }

        id += today;
        counter += 1;
    }

    return counter;
}

int main() {
    int test_count; std::cin >> test_count;
    for (int i = 0; i < test_count; i++) {
        std::cout << solve_test() << "\n";
    }
    return 0;
}
