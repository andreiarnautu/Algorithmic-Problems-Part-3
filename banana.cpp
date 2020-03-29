/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>

int main() {
    std::string s; std::cin >> s;
    int n; std::cin >> n;

    const int sigma = 26;

    std::vector<int> f(sigma, 0);
    for (int i = 0; i < (int)s.size(); i++) {
        f[s[i] - 'a']++;
    }

    for (int i = 1; i <= (int)s.size(); i++) {
        int need = 0;
        for (int j = 0; j < sigma; j++) {
            int needed_here = f[j] / i;
            if (f[j] % i != 0) {
                needed_here++;
            }
            need += needed_here;
        }

        if (need <= n) {
            std::cout << i << '\n';
            std::string result;

            for (int j = 0; j < sigma; j++) {
                int needed_here = f[j] / i;
                if (f[j] % i != 0) {
                    needed_here++;
                }

                while (needed_here) {
                    result += ('a' + j);
                    needed_here--;
                }
            }

            while ((int)result.size() < n) {
                result += 'a';
            }
            std::cout << result << '\n'; return 0;
        }
    }

    std::cout << "-1\n";
    return 0;
}
