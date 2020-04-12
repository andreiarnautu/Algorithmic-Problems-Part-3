/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("hagi.in"); std::ofstream fout("hagi.out");

const int MOD = 1e9 + 7;
const int MAX_VAL = 1e6 + 5;

long long fact[MAX_VAL * 2];

void compute_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAX_VAL * 2; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
}

long long raise(long long base, long long exp) {
    long long answer = 1, aux = base;
    for (long long i = 1; i <= exp; i <<= 1) {
        if (i & exp) {
            answer = answer * aux % MOD;
        }
        aux = aux * aux % MOD;
    }
    return answer;
}

long long comb(long long n, long long k) {
    long long a = raise(fact[k], MOD - 2);
    long long b = raise(fact[n - k], MOD - 2);
    long long down = a * b % MOD;
    return fact[n] * down % MOD;
}

int main(int argc, char **argv) {
    compute_factorials();
    int k, n, m; fin >> k >> n >> m;

    long long a = comb(n + k - 1, k - 1), b = comb(m + k - 1, k - 1);
    fout << a * b % MOD << "\n";

    return 0;
}
