/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<std::pair<int, int>> arr(n);
    for (auto& p: arr) {
        std::cin >> p.first >> p.second;
    }

    std::sort(arr.begin(), arr.end(), [&](std::pair<int, int> a, std::pair<int, int> b) {
        return a.first - a.second < b.first - b.second;
    });

    long long needed = 0;
    for (auto& p: arr) {
        needed += p.second;
        needed = std::max(needed, 1LL * p.first);
    }
    std::cout << needed << '\n';
    return 0;
}
