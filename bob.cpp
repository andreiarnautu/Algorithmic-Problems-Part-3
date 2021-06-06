/**
 *  Worg
 */
#include <bitset>
#include <vector>
#include <fstream>
#include <algorithm>

const char FILE_IN[] = "bob.in";
const char FILE_OUT[] = "bob.out";

class Solver {
public:
    Solver(const char* input_path, const char* output_path) {
        fin = std::ifstream(input_path);
        fout = std::ofstream(output_path);
    }

    void read_generic_data() {
        fin >> task >> test_number;
    }

    void solve_tests() {
        for (int i = 0; i < test_number; i++) {
            read_test_data();
            std::pair<int, int> result = compute_solution();
            solution.push_back((task == 1) ? result.first : result.second);
        }
        fin.close();
    }

    void write_output() {
        for (int i = 0; i < test_number; i++) {
            fout << solution[i] << '\n';
        }
        fout.close();
    }

private:
    static const int MOD = 1e9 + 7;
    static const int MAX_K = 20;

    std::ifstream fin;
    std::ofstream fout;

    int task, test_number;
    int n, k;
    std::vector<int> mask_arr;

    std::vector<int> dp_max, dp_cnt, sum_dp;
    std::vector<int> solution;

    void init_structures() {
        mask_arr.resize(n);
        dp_max.resize(n);
        dp_cnt.resize(n);
        sum_dp.resize(n);
    }

    void read_test_data() {
        fin >> n >> k;
        init_structures();

        std::string str_mask;
        for (int i = 0; i < n; i++) {
            fin >> str_mask;

            mask_arr[i] = 0;
            for (int j = 0; j < k; j++) {
                mask_arr[i] |= (str_mask[j] == '1') ? (1 << j) : 0;
            }
        }
    }

    void update_mask(std::vector<int>& mask, int value, int sign) {
        for (int i = 0; i < k; i++) {
            int bit_value = (value & (1 << i)) ? 1 : 0;
            mask[i] += bit_value * sign;
        }
    }

    bool is_valid(std::vector<int>& mask) {
        for (int i = 0; i < k; i++) {
            if (!mask[i]) {
                return false;
            }
        }
        return true;
    }

    std::pair<int, int> compute_solution() {
        int seq_start = 0;
        std::vector<int> current_mask(k, 0);

        for (int i = 0; i < n; i++) {
            update_mask(current_mask, mask_arr[i], +1);

            //  try to move the sequence start to the right, if possible
            bool flag = true;
            while (flag) {
                update_mask(current_mask, mask_arr[seq_start], -1);

                if (!is_valid(current_mask)) {
                    update_mask(current_mask, mask_arr[seq_start], +1);
                    flag = false;
                } else {
                    seq_start++;
                }
            }

            if (is_valid(current_mask)) {
                if (seq_start == 0) {
                    dp_max[i] = 1;
                    dp_cnt[i] = 1;

                    if (i > 0 && dp_max[i - 1] == 1) {
                        sum_dp[i] = sum_dp[i - 1] + 1;
                    } else {
                        sum_dp[i] = 1;
                    }
                } else {
                    dp_max[i] = dp_max[seq_start - 1] + 1;
                    dp_cnt[i] = sum_dp[seq_start - 1];

                    if (dp_max[i] == dp_max[i - 1]) {
                        sum_dp[i] = sum_dp[i - 1] + dp_cnt[i];

                        if (sum_dp[i] >= MOD) {
                            sum_dp[i] -= MOD;
                        }
                    } else {
                        sum_dp[i] = dp_cnt[i];
                    }
                }
            } else {
                dp_max[i] = 0;
                dp_cnt[i] = 1;
                sum_dp[i] = 1;
            }
        }

        return {dp_max.back(), dp_cnt.back()};
    }

};

int main() {
    Solver solver(FILE_IN, FILE_OUT);
    solver.read_generic_data();
    solver.solve_tests();
    solver.write_output();
    return 0;
}
