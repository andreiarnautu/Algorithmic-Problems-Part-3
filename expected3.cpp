/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("expected3.in");
std::ofstream fout("expected3.out");

const int MOD = 1e9 + 7;

long long n, m, a, b;

long long power(long long base, long long exp) {
    long long answer = 1, aux = base;

    for (long long i = 1; i <= exp; i <<= 1) {
        if (exp & i) {
            answer = answer * aux % MOD;
        }

        aux = aux * aux % MOD;
    }

    return answer;
}

int main(int argc, char **argv) {
    fin >> n >> m >> a >> b;

    long long result = ((a * n % MOD) - (b * m % MOD) + MOD) % MOD;
    result = result * power(2, MOD - 2) % MOD;
    fout << result;

    return 0;
}
