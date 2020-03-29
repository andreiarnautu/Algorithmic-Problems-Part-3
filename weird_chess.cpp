/**
  *  Worg
  */
#include <vector>
#include <iostream>

bool OutOfBoundaries(int x, int y, int n) {
    return x < 0 || y < 0 || x >= n || y >= n;
}

int main() {
    int n; std::cin >> n;
    std::vector<std::vector<char>> table(n, std::vector<char>(n, 0));
    std::vector<std::pair<int, int>> pieces;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> table[i][j];

            if (table[i][j] == 'o') {
                pieces.emplace_back(i, j);
            }
        }
    }


    std::vector<std::vector<char>> answer(2 * n - 1, std::vector<char>(2 * n - 1, '.'));
    std::vector<std::pair<int, int>> good_moves;

    for (int dx = -(n - 1); dx <= (n - 1); dx++) {
        for (int dy = -(n - 1); dy <= (n - 1); dy++) {
            bool verdict = true;

            for (std::pair<int, int> piece : pieces) {
                int new_x = piece.first + dx, new_y = piece.second + dy;

                if (OutOfBoundaries(new_x, new_y, n) || table[new_x][new_y] == 'x' || table[new_x][new_y] == 'o') {
                    //  lol
                } else {
                    verdict = false;
                }
            }

            if (verdict) {
                good_moves.emplace_back(dx, dy);
            }
        }
    }

    //  Check if there are any x positions uncovered.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (table[i][j] == 'x') {
                bool verdict = false;

                for (std::pair<int, int> move : good_moves) {
                    int prev_x = i - move.first, prev_y = j - move.second;

                    if (!OutOfBoundaries(prev_x, prev_y, n) && table[prev_x][prev_y] == 'o') {
                        verdict = true; break;
                    }
                }

                if (!verdict) {
                    std::cout << "NO\n"; return 0;
                }
            }
        }
    }

    for (std::pair<int, int> move : good_moves) {
        answer[move.first + (n - 1)][move.second + (n - 1)] = 'x';
    }
    answer[n - 1][n - 1] = 'o';

    std::cout << "YES\n";
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            std::cout << answer[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}
