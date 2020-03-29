/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int w, m; std::cin >> w >> m;

    std::vector<int> v;
    while (m) {
        v.push_back(m % w);
        m /= w;
    }

    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == w || v[i] == w - 1) {
            if (v[i] == 1) continue;
            if (i + 1 < (int)v.size()) {
                v[i + 1] += 1;
            } else {
                v.push_back(1);
            }
        } else if (v[i] != w && v[i] != w - 1 && v[i] != 1 && v[i] != 0) {
            std::cout << "NO\n"; return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}
