/**
  *  Worg
  */
#include <vector>
#include <iostream>

bool Fantastik(int x) {
    std::vector<bool> seen(10);

    do {
        if (seen[x % 10]) {
            return false;
        }
        seen[x % 10] = true;
        x /= 10;
    } while (x > 0);

    return true;
}


int main() {
    int left, right; std::cin >> left >> right;

    for (int i = left; i <= right; i++) {
        if (Fantastik(i)) {
            std::cout << i << '\n'; return 0;
        }
    }
    std::cout << "-1\n";
    return 0;
}
