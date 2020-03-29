/**
  *  Worg
  */
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n; std::cin >> n;

    std::multiset<int> mset;
    for (int i = 0; i < (1 << n); i++) {
        int x; std::cin >> x;
        mset.insert(-x);
    }

    std::multiset<int> a, b;
    a.insert(*mset.begin()); mset.erase(mset.begin());

    for (int i = 1; i <= n; i++) {
        for (auto& x: a) {
            auto it = mset.upper_bound(x);

            if (it == mset.end()) {
                std::cout << "No\n"; return 0;
            }

            b.insert(*it); mset.erase(it);
        }

        for (auto& x: b) {
            a.insert(x);
        }
        b.clear();
    }

    std::cout << "Yes\n";
    return 0;
}
