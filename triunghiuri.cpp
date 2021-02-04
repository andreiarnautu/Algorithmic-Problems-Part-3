/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("triunghiuri.in");
std::ofstream fout("triunghiuri.out");

int n, q;
int count[2][2], local_count[2][2];

int determinant(int x0, int y0, int x1, int y1, int x2, int y2) {
    return (x0 * y1 + x1 * y2 + x2 * y0) - (x2 * y1 + x1 * y0 + x0 * y2);
}

long long count_triangles() {
    long long answer = 0;

    for (int state_0 = 0; state_0 < 4; state_0++) {
        for (int state_1 = state_0; state_1 < 4; state_1++) {
            for (int state_2 = state_1; state_2 < 4; state_2++) {
                int x0 = state_0 >> 1, y0 = state_0 & 1;
                int x1 = state_1 >> 1, y1 = state_1 & 1;
                int x2 = state_2 >> 1, y2 = state_2 & 1;
                int determinant_parity = determinant(x0, y0, x1, y1, x2, y2) & 1;

                if (determinant_parity == 0) {
                    //  Count how many combinations we have
                    if (state_0 == state_1 && state_1 == state_2) {
                        long long a = count[x0][y0];
                        answer += a * (a - 1) * (a - 2) / 6;
                    } else if (state_0 == state_1) {
                        long long a = count[x0][y0];
                        long long b = count[x2][y2];
                        answer += a * (a - 1) / 2 * b;
                    } else if (state_1 == state_2) {
                        long long a = count[x0][y0];
                        long long b = count[x1][y1];
                        answer += a * b * (b - 1) / 2;
                    } else {
                        answer += count[x0][y0] * count[x1][y1] * count[x2][y2];
                    }
                }
            }
        }
    }

    return answer;
}

int main(int argc, char **argv) {
    fin >> n >> q;
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        x = std::max(x, -x);
        y = std::max(y, -y);
        count[x & 1][y & 1]++;
    }

    fout << count_triangles() << "\n";

    for (int i = 0; i < q; i++) {
        int type, x, y; fin >> type >> x >> y;
        x = std::max(x, -x);
        y = std::max(y, -y);
        if (type == 1) {
            count[x & 1][y & 1]++;
        } else {
            count[x & 1][y & 1]--;
        }

        fout << count_triangles() << "\n";
    }
    return 0;
}
