/**
  *  Worg
  */
#include <fstream>
#include <iostream>

std::ifstream fin("copii.in"); std::ofstream fout("copii.out");

const int MAX_N = 10;

bool a[MAX_N][MAX_N], rel[MAX_N][MAX_N];
int grp[MAX_N];

void Check(const int& n, int& answer, const int& cnt_grp) {
    if (cnt_grp == 1) return;

    for (int i = 0; i < cnt_grp; i++) {
        for (int j = 0; j < cnt_grp; j++) {
            rel[i][j] = (i == j);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rel[grp[i]][grp[j]] |= a[i][j];
        }
    }

    for (int i = 0; i < cnt_grp; i++) {
        for (int j = 0; j < cnt_grp; j++) {
            if (rel[i][j] == 0) {
                return;
            }
        }
    }
    answer++;
}

void Back(const int& n, int& answer, int idx, int cnt_grp) {
    if (idx == n) {
        Check(n, answer, cnt_grp);
        return;
    }

    for (int i = 0; i < cnt_grp; i++) {
        grp[idx] = i;
        Back(n, answer, idx + 1, cnt_grp);
    }

    grp[idx] = cnt_grp;
    Back(n, answer, idx + 1, cnt_grp + 1);
}

int main() {
    int n, answer = 0; fin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; fin >> c;
            a[i][j] = (c == '1');
        }
    }

    Back(n, answer, 1, 1);
    fout << answer << '\n';
    return 0;
}
