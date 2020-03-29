/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> tst(n);
    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        for (int j = 0; j < k; j++) {
            int x, y; std::cin >> x >> y;
            tst[i].emplace_back(x - 1, y);
        }
    }

    int answer = 0;
    const int max_mask = 1 << n;
    for (int mask = 0; mask < max_mask; mask++) {
        bool verdict = true;
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                total += 1;
                for (auto& p: tst[i]) {
                    int hmm = (mask & (1 << p.first)) ? 1 : 0;

                    if (hmm ^ p.second) {
                        verdict = false;
                    }
                }
            }
        }

        answer = std::max(answer, total * verdict);
    }

    std::cout << answer << "\n";
    return 0;
}
