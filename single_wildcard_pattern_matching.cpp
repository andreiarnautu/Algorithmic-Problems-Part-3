/**
  *  Worg
  */
#include <string>
#include <iostream>

int main() {
    int n, m; std::cin >> n >> m;
    int has_star = false;
    std::string s, t; std::cin >> s >> t;

    for (int i = 0; i < n; i++) {
        if (s[i] == '*') {
            has_star = true;
        }
    }

    if (has_star && m + 1 < n) {
        std::cout << "NO\n"; return 0;
    }
    if (!has_star && m != n) {
        std::cout << "NO\n"; return 0;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '*') break;

        if (s[i] != t[i]) {
            std::cout << "NO\n"; return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (s[n - i - 1] == '*') break;

        if (s[n - i - 1] != t[m - i - 1]) {
            std::cout << "NO\n"; return 0;
        }
    }

    std::cout << "YES\n";
    return 0;
}
