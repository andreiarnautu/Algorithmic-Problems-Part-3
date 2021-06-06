/**
 *  Worg
 */
#include <bitset>
#include <vector>
#include <fstream>
#include <algorithm>

const char FILE_IN[] = "tort4.in";
const char FILE_OUT[] = "tort4.out";
const int MAX_SUM = 4e5 + 1;

class Solver {
public:
    Solver() {
        fin = std::ifstream(FILE_IN);
        fout = std::ofstream(FILE_OUT);
        solution = 0;
    }

    void read_input() {
        fin >> n;
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            fin >> arr[i];
        }
        fin.close();
    }

    void compute_solution() {
        //  store partial sums' values
        int partial_sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            partial_sum += arr[i];
            seen[partial_sum] = 1;
        }

        //  try each possible sequence value
        for (int value = 1; value < partial_sum; value++) {
            for (int i = value; i < partial_sum; i += value) {
                if (seen[i] == 1) {
                    solution++;
                } else {
                    break;
                }
            }
        }
    }

    void write_output() {
        fout << solution << '\n';
        fout.close();
    }

private:
    std::ifstream fin;
    std::ofstream fout;
    int n;
    std::vector<int> arr;
    std::bitset<MAX_SUM> seen;

    int solution;
};

int main() {
    Solver solver;
    solver.read_input();
    solver.compute_solution();
    solver.write_output();
    return 0;
}

