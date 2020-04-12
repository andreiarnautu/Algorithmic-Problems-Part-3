/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("covrigi.in"); std::ofstream fout("covrigi.out");

int main(int argc, char **argv) {
    long long n, m, k; fin >> n >> m >> k;
    std::vector<long long> v(n), c(m);

    int current_place = 0;
    for (auto& elem : v) {
        fin >> elem;
    }
    for (auto& elem : c) {
        fin >> elem;
        current_place += elem;
    }

    std::sort(c.begin(), c.end(), [&](long long a, long long b) {
        return a > b;
    });

    long long best_answer = v[current_place], current_pay = 0;
    for (auto& elem : c) {
        current_pay += k;
        current_place -= elem;
        if (current_place < 0) {
            break;
        }

        best_answer = std::max(best_answer, v[current_place] - current_pay);
    }

    fout << best_answer << "\n";
    return 0;
}
