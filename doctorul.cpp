/**
  *  Worg
  *  Brutul ala blana
  */
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

const int inf = 2e5;

int main() {
    std::string str; std::cin >> str;
    int query_count; std::cin >> query_count;

    for (int i = 0; i < query_count; i++) {
        int Q, limitaInf, limitaSup, S, D; std::cin >> Q >> limitaInf >> limitaSup >> S >> D;

        std::pair<int, int> ans = {inf, inf};

        std::vector<int> freq(300);
        for (int j = S; j <= D; j++) {
            for (int k = 'a'; k <= 'z'; k++) {
                freq[k] = 0;
            }

            int count_different = 0;
            for (int k = j; k <= D; k += 1) {
                freq[str[k]]++;
                if (freq[str[k]] == 1) {
                    count_different++;
                }

                if (count_different == Q && limitaInf <= k - j + 1 && k - j + 1 <= limitaSup) {
                    ans = std::min(ans, std::make_pair(j, k));
                }
            }
        }

        if (ans == std::make_pair(inf, inf)) {
            std::cout << "-1 -1\n";
        } else {
            std::cout << ans.first << " " << ans.second << '\n';
        }
    }

    return 0;
}
