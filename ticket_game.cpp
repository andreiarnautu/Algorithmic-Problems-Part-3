/**
  *  Worg
  */
#include <string>
#include <iostream>

int main() {
    int n; std::cin >> n;
    std::string digits; std::cin >> digits;

    int balance = 0;
    for (int i = 0; i < n; i++) {
        int x;

        if (digits[i] == '?') {
            x = 9;
        } else {
            x = 2 * (digits[i] - '0');
        }

        if (i < n / 2) {
            balance += x;
        } else {
            balance -= x;
        }
    }

    if (balance == 0) {
        std::cout << "Bicarp\n";
    } else {
        std::cout << "Monocarp\n";
    }
}
