/**
  *  Worg
  */
#include <vector>
#include <fstream>

std::ifstream fin("damesah.in"); std::ofstream fout("damesah.out");

int count;
std::vector<int> current_solution;
std::vector<int> first_solution;
std::vector<bool> col, diag1, diag2;

void Back(int row, const int& n) {
    if (row == n + 1) {
        count += 1;
        if (count == 1) {
            first_solution = current_solution;
        }

        return;
    }

    for (int i = 1; i <= n; i++) {
        if (col[i] == 1 || diag1[row - i + n] == 1 || diag2[row + i - 1]) {
            continue;
        }
        current_solution[row] = i;
        col[i] = true;
        diag1[row - i + n] = true;
        diag2[row + i - 1] = true;

        Back(row + 1, n);

        col[i] = false;
        diag1[row - i + n] = false;
        diag2[row + i - 1] = false;
    }
}

int main(int argc, char **argv) {
    int n; fin >> n;

    col = std::vector<bool>(n + 1, false);
    diag1 = diag2 = std::vector<bool>(2 * n, false);

    current_solution = first_solution = std::vector<int>(n + 1);
    Back(1, n);

    for (int i = 1; i <= n; i++) {
        fout << first_solution[i] << " ";
    }
    fout << '\n' << count << '\n';
    return 0;
}