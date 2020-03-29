/**
  *  Worg
  */
#include <iostream>

int main() {
    long long r; std::cin >> r;
    r--;
    
    for (long long x = 1; x * x <= r; x++) {
        if (r % x == 0) {
            long long y = r / x - x - 1;

            if (y > 0 && y % 2 == 0) {
                std::cout << x << " " << y / 2 << '\n'; return 0;
            }
        }
    }

    std::cout << "NO\n";

    return 0;
}
