/**
  *  Worg
  */
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

void solve_test() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), freq(n + 1, 0), ends(n + 1, 0);
    int cut_count = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        freq[a[i]] += 1;

        if (i > 0 && a[i] == a[i - 1]) {
            ends[a[i]] += 1;
            ends[a[i - 1]] += 1;
            cut_count += 1;
        }
    }

    if (*std::max_element(freq.begin(), freq.end()) > (n + 1) / 2) {
        std::cout << "-1\n"; return;
    }

    ends[a[0]] += 1;
    ends[a[n - 1]] += 1;
    int max_freq = *std::max_element(ends.begin(), ends.end());
    std::cout << cut_count + std::max(0, max_freq - cut_count - 2) << '\n';
}

int main() {
    int test_count;
    std::cin >> test_count;
    for (int test = 0; test < test_count; test++) {
        solve_test();
    }

    return 0;
}
