/**
 *  Worg
 */
#include <cstdio>
#include <vector>
#include <cstdlib>

#define AND_GATE     0
#define OR_GATE      1

const char FILE_IN[] = "logic3.in";
const char FILE_OUT[] = "logic3.out";
const int MOD = 666013;

std::vector<std::vector<bool>> read_gates(FILE *fp_in, int n) {
    std::vector<std::vector<bool>> gates;

    char *buffer = (char*) malloc((1 << (n - 1)) + 1);
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%s", buffer);

        std::vector<bool> level(1 << i);
        for (int j = 0; j < (int)level.size(); j++) {
            if (buffer[j] == '&') {
                level[j] = AND_GATE;
            } else {
                level[j] = OR_GATE;
            }
        }

        gates.push_back(level);
    }

    return gates;
}

int eval_input(int n, std::vector<std::vector<bool>>& gates, FILE *fp_in) {
    std::vector<bool> current_level, next_level;

    //  parse input
    current_level.resize(1 << n);
    char *buffer = (char*) malloc((1 << n) + 1);
    fscanf(fp_in, "%s", buffer);
    for (int i = 0; i < (1 << n); i++) {
        current_level[i] = buffer[i] - '0';
    }

    for (int level = n - 1; level >= 0; level--) {
        //  get the inputs for the next level
        next_level = std::vector<bool>(1 << level);

        for (int i = 0, j = 0; j < (1 << level); i += 2, j++) {
            if (gates[level][j] == AND_GATE) {
                next_level[j] = current_level[i] & current_level[i + 1];
            } else {
                next_level[j] = current_level[i] | current_level[i + 1];
            }
        }

        current_level = next_level;
    }

    return current_level.back();
}

int count(int n, std::vector<std::vector<bool>>& gates, bool result) {
    std::vector<int> count[2], next_count[2];

    //  initialize for the last row
    count[0].resize(1 << n); count[1].resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        count[0][i] = count[1][i] = 1;
    }

    for (int level = n - 1; level >= 0; level--) {
        //  compute number of configurations for having 0/1 for the next level
        next_count[0] = std::vector<int>(1 << level);
        next_count[1] = std::vector<int>(1 << level);

        for (int i = 0, j = 0; j < (1 << level); i += 2, j++) {
            if (gates[level][j] == AND_GATE) {
                //  for 0 - we need at least a 0
                next_count[0][j] = (1LL * count[0][i] * count[0][i + 1] +
                                    1LL * count[0][i] * count[1][i + 1] +
                                    1LL * count[1][i] * count[0][i + 1]) % MOD;
                //  for 1 - we need both to be 1
                next_count[1][j] = 1LL * count[1][i] * count[1][i + 1] % MOD;
            } else {
                //  for 0 - we need both to be 0
                next_count[0][j] = 1LL * count[0][i] * count[0][i + 1] % MOD;
                //  for 1 - we need at least a 1
                next_count[1][j] = (1LL * count[0][i] * count[1][i + 1] +
                                    1LL * count[1][i] * count[0][i + 1] +
                                    1LL * count[1][i] * count[1][i + 1]) % MOD;
            }
        }

        count[0] = next_count[0];
        count[1] = next_count[1];
    }

    return count[result].back();
}

int main(int argc, char **argv) {
    FILE *fp_in = fopen(FILE_IN, "r");
    FILE *fp_out = fopen(FILE_OUT, "w");

    int task, n;
    fscanf(fp_in, "%d%d", &task, &n);
    std::vector<std::vector<bool>> gates = read_gates(fp_in, n);

    if (task == 1) {
        int k;
        fscanf(fp_in, "%d", &k);
        for (int i = 0; i < k; i++) {
            fprintf(fp_out, "%d\n", eval_input(n, gates, fp_in));
        }
    } else {
        int result;
        fscanf(fp_in, "%d", &result);

        int input_count = count(n, gates, result);
        fprintf(fp_out, "%d\n", input_count);
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
