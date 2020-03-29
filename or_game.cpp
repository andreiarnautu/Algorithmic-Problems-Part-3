/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n, k, x; std::cin >> n >> k >> x;

    std::vector<long long> a(n + 1), or_pref(n + 2, 0), or_suff(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        or_pref[i] = or_pref[i - 1] | a[i];
    }
    for (int i = n; i >= 1; i--) {
        or_suff[i] = or_suff[i + 1] | a[i];
    }

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        long long current = a[i];
        for (int j = 1; j <= k; j++) {
            current *= x;
        }

        answer = std::max(answer, current | or_pref[i - 1] | or_suff[i + 1]);
    }
    std::cout << answer << '\n';
    return 0;
}
