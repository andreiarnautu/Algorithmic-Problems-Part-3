/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int INF = 1e9;

int main(int argc, char **argv) {
    int n; std::cin >> n;

    std::vector<int> v(n);
    for (auto& elem : v) {
        std::cin >> elem;
    }

    //  Precalculam modulele, pentru ca sunt operatii costisitoare si s-ar face de foarte multe ori altfel
    std::vector<std::vector<int>> modulos(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            modulos[i][j] = v[i] % v[j];
        }
    }

    std::vector<int> dp(1 << n, INF);
    dp[0] = 0;

    for (int bits = 0; bits < (1 << n); bits++) {
        if (dp[bits] != INF) {  //  sarim peste configuratiile imposibile, adica alea cu nr impar de biti setati
            //  try to choose 2 unused bits
            for (int i = 0; i < n; i++) {
                if (!(bits & (1 << i))) {
                    for (int j = i + 1; j < n; j++) {
                        if (!(bits & (1 << j))) {
                            int value = std::min(modulos[i][j], modulos[j][i]);
                            int new_bits = bits | (1 << i) | (1 << j);
                            dp[new_bits] = std::min(dp[new_bits], dp[bits] + value);
                        }
                    }
                }
            }
        }
    }
    std::cout << dp[(1 << n) - 1] << '\n';

    return 0;
}
