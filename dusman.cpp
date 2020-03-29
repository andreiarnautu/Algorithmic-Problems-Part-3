/**
  *  Worg
  */
#include <vector>
#include <bitset>
#include <fstream>
#include <cstdlib>

const int MAX_N = 1000 + 1;

std::ifstream fin("dusman.in"); std::ofstream fout("dusman.out");

bool enemies[MAX_N][MAX_N];

void print(std::vector<int>& curr_perm) {
    for (int& num : curr_perm) {
        fout << num << " ";
    }
    fout << '\n';
    fin.close(); fout.close();
    exit(0);
}

void back(int step, const int& n, int& k, std::vector<bool>& used, std::vector<int>& curr_perm) {
    if (step == n) {
        if (--k == 0) {
            print(curr_perm);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            if (step == 0 || !enemies[curr_perm[step - 1]][i]) {
                curr_perm[step] = i;
                used[i] = true;
                back(step + 1, n, k, used, curr_perm);
                used[i] = false;
            }
        }
    }
}

int main() {
    int n, k, m; fin >> n >> k >> m;

    for (int i = 0; i < m; i++) {
        int x, y; fin >> x >> y;
        enemies[x][y] = enemies[y][x] = true;
    }

    std::vector<int> curr_perm(n);
    std::vector<bool> used(n + 1, false);

    back(0, n, k, used, curr_perm);
    return 0;
}