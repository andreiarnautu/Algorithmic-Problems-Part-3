/**
  *  Worg
  */
#include <vector>
#include <iostream>

bool Check(int x, int y, int n, std::vector<std::vector<int>> &a) {
    for (int i = x - 2; i <= x; i++) {
        for (int j = y - 2; j <= y; j++) {
            if (i < 1 || j < 1 || i + 2 > n || j + 2 > n) continue;

            bool valid = true;
            for (int k1 = i; k1 <= i + 2; k1++) {
                for (int k2 = j; k2 <= j + 2; k2++) {
                    if (a[k1][k2] == false) {
                        valid = false;
                    }
                }
            }

            if (valid) {
                return true;
            }
        }
    }

    return false;
}


int main() {
    int n; std::cin >> n;
    std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1, 0));

    int m; std::cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y; std::cin >> x >> y;
        a[x][y] = 1;

        bool verdict = Check(x, y, n, a);
        if (verdict) {
            std::cout << i + 1 << '\n'; return 0;
        }
    }

    std::cout << "-1\n";
    return 0;
}
