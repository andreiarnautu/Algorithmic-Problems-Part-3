/**
  *  Worg
  */
#include <cmath>
#include <bitset>
#include <iostream>

const int MAX_SQRT = 1e6;
std::bitset<MAX_SQRT + 1> flag;

void compute_primes() {
    flag[0] = flag[1] = 1;

    for (int i = 2; i * i <= MAX_SQRT; i++) {
        if (flag[i] == 0) {
            for (int j = 2 * i; j <= MAX_SQRT; j += i) {
                flag[j] = 1;
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    compute_primes();

    int n; std::cin >> n;

    for (int i = 0; i < n; i++) {
        long long x; std::cin >> x;

        long long answer = sqrt((double)x);
        if (answer * answer == x && flag[answer] == 0) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
