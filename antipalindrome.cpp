/**
  *  Worg
  */
#include <string>
#include <iostream>

int main() {
    std::string s; std::cin >> s;

    for (int size = (int)s.size(); size > 1; size--) {
        for (int i = 0; i + size <= (int)s.size(); i++) {
            bool verdict = false;

            for (int left = i, right = i + size - 1; left <= right; left++, right--) {
                if (s[left] != s[right]) {
                    verdict = true;
                }
            }

            if (verdict) {
                std::cout << size << '\n'; return 0;
            }
        }
    }

    std::cout << "0\n";
    return 0;
}
