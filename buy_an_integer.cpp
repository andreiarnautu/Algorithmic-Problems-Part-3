/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const long long MAX_VALUE = 1e9;

int main() {
    long long a, b, x; std::cin >> a >> b >> x;
    long long answer = 0;

    for (long long digits = 1, base = 1; digits <= 10; digits++, base *= 10) {
        long long r = x - b * digits;

        if (r >= 0 && r / a >= base) {
            answer = std::min(base * 10 - 1, r / a);
        }
    }

    std::cout << std::min(answer, MAX_VALUE) << "\n";
    return 0;
}
