/**
  *  Worg
  */
#include <vector>
#include <iostream>

int main() {
    int n, m; std::cin >> n >> m;

    std::vector<std::pair<int, int>> flats(m);
    for (int i = 0; i < m; i++) {
        std::cin >> flats[i].first >> flats[i].second;
    }

    int answer = -1;
    for (int flat_count = 1; flat_count <= 100; flat_count++) {
        bool possible = true;

        for (std::pair<int, int> flat : flats) {
            int expected = 1 + (flat.first - 1) / flat_count;

            if (expected != flat.second) {
                possible = false; break;
            }
        }

        if (possible) {
            int expected = 1 + (n - 1) / flat_count;

            if (answer != -1 && expected != answer) {
                std::cout << "-1\n"; return 0;
            }
            answer = expected;
        }
    }
    std::cout << answer << '\n';
    return 0;
}
