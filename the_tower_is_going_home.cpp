/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_VALUE = 1e9;

int main(int argc, char const *argv[]) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> vert(n), hor;

    for (int i = 0; i < n; i++) {
        std::cin >> vert[i];
    }

    for (int i = 0; i < m; i++) {
        int x1, x2, y; std::cin >> x1 >> x2 >> y;

        if (x1 == 1) {
            hor.push_back(x2);
        }
    }

    std::sort(hor.begin(), hor.end());
    std::sort(vert.begin(), vert.end());
    vert.push_back(MAX_VALUE);

    int count_hor = 0;
    while (count_hor < (int)hor.size() && hor[count_hor] < vert[0]) {
        count_hor += 1;
    }

    int answer = n + m;
    for (int i = 0; i <= n; i++) {
        answer = std::min(answer, i + (int)hor.size() - count_hor);

        while (count_hor < (int)hor.size() && hor[count_hor] < vert[i + 1]) {
            count_hor += 1;
        }
    }

    std::cout << answer << '\n';
    return 0;
}
