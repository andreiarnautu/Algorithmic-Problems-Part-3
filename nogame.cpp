/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("nogame.in"); std::ofstream fout("nogame.out");

const int num_ops = 16;

std::vector<std::vector<std::vector<int>>> Generate() {
    std::vector<std::vector<std::vector<int>>> ops;
    for (int i1 = 0; i1 < 2; i1++) {
        for (int i2 = 0; i2 < 2; i2++) {
            for (int i3 = 0; i3 < 2; i3++) {
                for (int i4 = 0; i4 < 2; i4++) {
                    std::vector<std::vector<int>> v(2, std::vector<int>(2));
                    v[0][0] = i1; v[0][1] = i2; v[1][0] = i3; v[1][1] = i4;
                    ops.push_back(v);
                }
            }
        }
    }

    return ops;
}

int GetNumber(std::vector<std::vector<int>> &op, int a, int b) {
    int bit = 1, result = 0;

    do {
        int b1 = 0, b2 = 0;

        if (a & bit) {
            b1 = 1;
        }
        if (b & bit) {
            b2 = 1;
        }
        result += bit * op[b1][b2];
        bit *= 2;
    } while (bit <= a || bit <= b);

    return result;
}

int main() {
    std::vector<std::vector<std::vector<int>>> ops = Generate();

    int test_cases; fin >> test_cases;

    while (test_cases--) {
        int n; fin >> n;

        std::vector<std::vector<int>> arr(num_ops, std::vector<int>(n));
        for (int i = 0; i < num_ops; i++) {
            for (int j = 0; j < n; j++) {
                fin >> arr[i][j];
            }
        }

        std::sort(arr.begin(), arr.end());

        for (int i = 0; i < num_ops; i++) {
            std::vector<std::vector<int>> new_arr(num_ops, std::vector<int>(n));

            for (int j = 0; j < num_ops; j++) {
                new_arr[j][0] = arr[i][0];

                for (int k = 1; k < n; k++) {
                    new_arr[j][k] = GetNumber(ops[j], new_arr[j][k - 1], arr[i][k]);
                }
            }

            std::sort(new_arr.begin(), new_arr.end());

            bool good = true;
            for (int j = 0; j < num_ops && good; j++) {
                for (int k = 0; k < n && good; k++) {
                    if (arr[j][k] != new_arr[j][k]) {
                        good = false;
                    }
                }
            }

            if (good) {
                for (int j = 0; j < n; j++) {
                    fout << arr[i][j] << " ";
                }
                fout << '\n'; break;
            } else if (!good && i == num_ops - 1) {
                fout << "-1\n";
            }
        }
    }
    return 0;
}
