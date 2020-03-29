/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<int> a(n);
    for (auto& x: a) {
        std::cin >> x;
    }

    std::sort(a.begin(), a.end());
    std::vector<long long> sum(m, 0);
    long long answer = 0;
    for (int i = 0; i < n; i++) {
        answer += sum[i % m];
        sum[i % m] += a[i];
        answer += a[i];
        std::cout << answer << " ";
    }
    std::cout << "\n";
    return 0;
}
