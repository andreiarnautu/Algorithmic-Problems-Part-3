/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


int main() {
    std::string s; std::cin >> s;
    int ans = 0, prv = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        ans += 1;
        if (prv != 1 || s[i] != s[i - 1]) {
            prv = 1;
        } else if (i + 1 == (int)s.size()) {
            ans -= 1;
        } else {
            prv = 2;
            i += 1;
        }

    }

    std::cout << ans << "\n";
    return 0;
}
