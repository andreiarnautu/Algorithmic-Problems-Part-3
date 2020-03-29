/**
  *  Worg
  */
#include <cmath>
#include <vector>
#include <iostream>

int ans = 20;

void Check(int cnt, const std::vector<int> &digits) {
    int x = 0;

    for (int i = (int)digits.size() - 1; i >= 0; i--) {
        x = x * 10 + digits[i];
    }

    int root = std::sqrt(x);
    if (root * root == x) {
        ans = cnt;
    }
}

void Back(int cnt, std::vector<int> digits) {
    if (cnt > ans) return;
    Check(cnt, digits);

    if (digits.size() == 1) return;

    if (digits[digits.size() - 2] != 0) {
        std::vector<int> new_digits(digits);
        new_digits.pop_back();
        Back(cnt + 1, new_digits);
    }

    for (int i = 0; i < (int)digits.size() - 1; i++) {
        std::vector<int> new_digits;

        for (int j = 0; j < (int)digits.size(); j++) {
            if (j != i) {
                new_digits.push_back(digits[j]);
            }
        }

        Back(cnt + 1, new_digits);
    }
}

int main() {
    int n; std::cin >> n;

    std::vector<int> digits;
    while (n) {
        digits.push_back(n % 10);
        n /= 10;
    }

    Back(0, digits);
    if (ans == 20) {
        std::cout << "-1\n";
    } else {
        std::cout << ans << '\n';
    }
    return 0;
}
