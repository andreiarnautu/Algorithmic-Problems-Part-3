/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("nane.in"); std::ofstream fout("nane.out");

const int MAX_BITS = 31;

int main() {
    int n, k; fin >> n >> k;
    std::vector<int> v(n);
    for (auto& elem : v) {
        fin >> elem;
    }

    long long ans = 0;
    std::vector<int> nxt(MAX_BITS, n), curr(MAX_BITS);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < MAX_BITS; j++) {
            if (v[i] & (1 << j)) {
                nxt[j] = i;
            }
            curr[j] = nxt[j];
        }
        std::sort(curr.begin(), curr.end());
        ans += (curr[std::min(k, MAX_BITS - 1)] - i);
    }

    fout << ans << "\n";
    return 0;
}
