/**
 *  Worg
 */
#include <vector>
#include <fstream>
#include <algorithm>

const char FILE_IN[] = "sdistante.in";
const char FILE_OUT[] = "sdistante.out";

class Solver {
public:
    Solver() {
        fin = std::ifstream(FILE_IN);
        fout = std::ofstream(FILE_OUT);
        weight = std::vector<long long>(ALPHABET_SIZE, 0);
        solution = 0;
    }

    void read_input() {
        fin >> s;
        fin.close();
    }

    void compute_solution() {
        int n = (int)s.size();
        weight[char_value(s[n - 1])] = 1;

        for (int i = n - 2; i >= 0; i--) {
            //  compute no. of differences with next characters
            long long total_weight = 1LL * (1LL * (n - i) * (n - i - 1) / 2) % MOD *
                                     (i + 1) % MOD;

            long long char_weight = weight[char_value(s[i])] * (i + 1) % MOD;

            solution += (total_weight - char_weight);
            solution %= MOD;

            //  update character weight
            weight[char_value(s[i])] += (n - i);
        }
    }

    void write_solution() {
        fout << solution << '\n';
        fout.close();
    }

private:
    static const int MOD = 1e9 + 7;
    static const int ALPHABET_SIZE = 52;

    std::ifstream fin;
    std::ofstream fout;

    std::string s;
    std::vector<long long> weight;
    long long solution;

    int char_value(char c) {
        return ('a' <= c && c <= 'z') ? (c - 'a') : (c - 'A' + 26);
    }
};

int main() {
    Solver solver;
    solver.read_input();
    solver.compute_solution();
    solver.write_solution();
    return 0;
}
