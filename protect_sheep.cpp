/**
  *  Worg
  */
#include <vector>
#include <iostream>

bool InBounds(int x, int y, int n, int m) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<std::vector<char>> a(n, std::vector<char>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    const std::vector<std::pair<int,int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') {
                for (std::pair<int, int> d : dir) {
                    int x = i + d.first, y = j + d.second;

                    if (InBounds(x, y, n, m) && a[x][y] == 'W') {
                        std::cout << "No\n"; return 0;
                    }
                }
            }
        }
    }

    std::cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '.') {
                std::cout << 'D';
            } else {
                std::cout << a[i][j];
            }
        }
        std::cout << '\n';
    }
    return 0;
}
