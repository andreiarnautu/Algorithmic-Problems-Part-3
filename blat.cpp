/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("blat.in"); std::ofstream fout("blat.out");

const int INF = 1e9;

int main(int argc, char **argv) {
    int n, m, k; fin >> m >> n >> k;
    std::vector<std::vector<int>> mat(k, std::vector<int>(m));

    for (auto& line : mat) {
        for (auto& x : line) {
            fin >> x;
        }
    }

    std::vector<int> cols;
    for (int j = 0; j < m; j++) {
        int sum_col = 0;
        for (int i = 0; i < k; i++) {
            sum_col += mat[i][j];
        }
        cols.push_back(sum_col);
    }

    std::sort(cols.begin(), cols.end());
    int sum_min = 0, sum_max = 0;
    for (int i = 0; i < n; i++) {
        sum_min += cols[i];
    }
    for (int i = m - 1; i > m - n - 1; i--) {
        sum_max += cols[i];
    }

    fout << sum_max << "\n" << sum_min << "\n";

    sum_min = INF, sum_max = -INF;
    for (int i = 0; i < k; i++) {
        std::sort(mat[i].begin(), mat[i].end());

        int curr_sum_min = 0, curr_sum_max = 0;
        for (int j = 0; j < n; j++) {
            curr_sum_min += mat[i][j];
        }
        for (int j = m - 1; j > m - n - 1; j--) {
            curr_sum_max += mat[i][j];
        }

        sum_min = std::min(sum_min, curr_sum_min);
        sum_max = std::max(sum_max, curr_sum_max);
    }
    fout << sum_max << "\n" << sum_min << "\n";
    return 0;
}
