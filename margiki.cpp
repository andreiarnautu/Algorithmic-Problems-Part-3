/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("margiki.in");
std::ofstream fout("margiki.out");

const int MOD = 1e9 + 7;
const int SIZE = 3;

long long n;
long long base[SIZE][SIZE], answer[SIZE][SIZE], aux[SIZE][SIZE];

void initialize() {
    base[0][1] = base[1][2] = base[2][0] = base[2][1] = base[2][2] = 1;
    answer[0][0] = answer[1][1] = answer[2][2] = 1;
}

void multiply(long long a[SIZE][SIZE], long long b[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            aux[i][j] = 0;
            for (int k = 0; k < SIZE; k++) {
                aux[i][j] += a[i][k] * b[k][j];
            }
            aux[i][j] %= MOD;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i][j] = aux[i][j];
        }
    }
}

void power(long long exp) {
    for (long long i = 1; i <= exp; i <<= 1) {
        if (exp & i) {
            multiply(answer, base);
        }
        multiply(base, base);
    }
}

int main(int argc, char **argv) {
    fin >> n;
    initialize();
    power(n);
    fout << answer[2][2];
    return 0;
}
