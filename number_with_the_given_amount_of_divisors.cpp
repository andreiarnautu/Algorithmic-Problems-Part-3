/**
  *  Worg
  */
#include <vector>
#include <iostream>


const long long MAX_VALUE = 1e18;
const int MAX_N = 1000;
const int MAX_EXP = 64;
// baze: 2, 3, 5, 7, 11, 13, 17, 19, 23
// exponenti:

std::vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23};
std::vector<std::vector<int>> divisors;
long long answer = MAX_VALUE;

void compute_divisors(int n) {
    divisors.resize(n + 1);

    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            for (int j = 2; j <= i; j++) {
                if (i % j == 0) {
                    divisors[i].push_back(j);
                }
            }
        }
    }
}

long long check_overflow(long long start, int multiplier, int exp) {
    for (int i = 1; i <= exp; i++) {
        if (answer / multiplier < start) {
            return -1;
        }
        start *= multiplier;
    }
    return start;
}

void back(int step, long long current_value, int rem, int max_div) {
    if (step == (int)bases.size()) {
        if (rem == 1) {
            answer = std::min(answer, current_value);
        }
        return;
    }

    back(step + 1, current_value, rem, 1);

    for (int& div : divisors[rem]) {
        if (div > max_div) {
            break;
        }

        long long result = check_overflow(current_value, bases[step], div - 1);
        if (result == -1) {
            break;
        }
        back(step + 1, result, rem / div, div);
    }
}

int main() {
    int n; std::cin >> n;
    compute_divisors(n);
    back(0, 1, n, MAX_EXP);
    std::cout << answer << '\n';
    return 0;
}