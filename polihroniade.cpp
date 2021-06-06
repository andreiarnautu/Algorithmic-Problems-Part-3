/**
 *  Worg
 */
#include <vector>
#include <fstream>
#include <algorithm>

const char FILE_IN[] = "polihroniade.in";
const char FILE_OUT[] = "polihroniade.out";

class Solver {
public:
    Solver(const char* input_path, const char* output_path) {
        fin = std::ifstream(input_path);
        fout = std::ofstream(output_path);
    }

    void read_generic_data() {
        fin >> task >> test_count;
    }

    void solve_tests() {
        for (int i = 0; i < test_count; i++) {
            read_test_data();
            switch (task) {
                case 1:
                    fout << check_validity() << '\n';
                    break;

                case 2:
                    build_solution();
                    fout << line_moves.size() + col_moves.size() << '\n';
                    break;

                case 3:
                    build_solution();

                    fout << line_moves.size() + col_moves.size() << '\n';

                    //  row and col ids should be 1-indexed, hence the +1
                    for (auto& move : line_moves) {
                        fout << "L " << move.first + 1 << ' ' << move.second + 1 << '\n';
                    }
                    for (auto& move : col_moves) {
                        fout << "C " << move.first + 1 << ' ' << move.second + 1 << '\n';
                    }
            }
        }
    }

    ~Solver() {
        fin.close();
        fout.close();
    }

private:
    std::ifstream fin;
    std::ofstream fout;

    int task, test_count;
    int n;
    std::vector<std::string> table;
    std::vector<std::pair<int, int>> line_moves, col_moves;

    void read_test_data() {
        fin >> n;
        table.resize(n);
        for (int i = 0; i < n; i++) {
            fin >> table[i];
        }
    }

    //  Returns 1 if lines are identical, 2 if complementary, 0 if neither.
    int compare(std::string& ref_line, std::string& line) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (ref_line[i] != line[i]) {
                flag = false;
                break;
            }
        }

        if (flag) return 1;

        flag = true;
        for (int i = 0; i < n; i++) {
            if (ref_line[i] == line[i]) {
                flag = false;
                break;
            }
        }

        return (flag == true) ? 2 : 0;
    }

    std::vector<std::string> get_transposed() {
        std::vector<std::string> table_transposed(n);
        for (int j = 0; j < n; j++) {
            table_transposed[j].resize(n);
            for (int i = 0; i < n; i++) {
                table_transposed[j][i] = table[i][j];
            }
        }

        return table_transposed;
    }

    bool check_lines(std::vector<std::string>& _table) {
        int count_identical = 1;
        int count_complementary = 0;

        for (int i = 1; i < n; i++) {
            int verdict = compare(_table[0], _table[i]);
            if (verdict == 1) {
                count_identical++;
            } else if (verdict == 2) {
                count_complementary++;
            } else {
                return false;
            }
        }

        return (count_identical == n / 2 && count_complementary == n / 2);
    }

    bool check_validity() {
        //  check lines
        bool flag_lines = check_lines(table);

        //  check columns
        std::vector<std::string> table_transposed = get_transposed();
        bool flag_columns = check_lines(table_transposed);

        return (flag_lines && flag_columns);
    }

    std::vector<std::pair<int, int>> compute_moves(std::string s) {
        int count_zeros[2] = {0, 0};
        int count_ones[2] = {0, 0};

        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                count_zeros[i & 1]++;
            } else {
                count_ones[i & 1]++;
            }
        }

        //  1010... vs 0101...
        std::vector<int> bad_zeros, bad_ones;
        int order = (count_zeros[0] < count_zeros[1]) ? 0 : 1;

        for (int i = 0; i < n; i++) {
            if (s[i] == '0' && (i & 1) == order) {
                bad_zeros.push_back(i);
            } else if (s[i] == '1' && (i & 1) == 1 - order) {
                bad_ones.push_back(i);
            }
        }

        std::vector<std::pair<int, int>> answer(bad_ones.size());
        for (int i = 0; i < (int)bad_ones.size(); i++) {
            answer[i] = {bad_zeros[i], bad_ones[i]};
        }
        return answer;
    }

    void build_solution() {
        col_moves = compute_moves(table[0]);

        std::string first_col;
        for (int i = 0; i < n; i++) {
            first_col += table[i][0];
        }

        line_moves = compute_moves(first_col);
    }
};

int main() {
    Solver solver(FILE_IN, FILE_OUT);
    solver.read_generic_data();
    solver.solve_tests();
    return 0;
}
