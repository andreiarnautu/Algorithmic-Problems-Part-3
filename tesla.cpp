/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

struct Move {
    int car_id, x, y;

    Move() {}
    Move(int _car_id, int _x, int _y) : car_id(_car_id), x(_x), y(_y) {}
};

int main() {
    int n, k; std::cin >> n >> k;

    int rem_cars = 0;
    std::vector<std::vector<int>> lot(4, std::vector<int>(n));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> lot[i][j];

            if ((i == 1 || i == 2) && lot[i][j] != 0) {
                rem_cars += 1;
            }
        }
    }

    std::vector<std::pair<int,int>> cycle;
    for (int it = 0; it < 2; it++) {
        for (int i = 0; i < n; i++) {
            cycle.emplace_back(1, i);
        }
        for (int i = n - 1; i >= 0; i--) {
            cycle.emplace_back(2, i);
        }
    }

    std::vector<Move> moves;
    while (rem_cars > 0) {
        // (1) verificam daca in configuratia curenta este vreo masina care este fix in dreptul locului corespunzator de parcare
        for (int i = 0; i < n; i++) {
            if (lot[0][i] == lot[1][i] && lot[0][i] != 0) {
                moves.emplace_back(lot[0][i], 0, i);
                lot[1][i] = 0;
                rem_cars -= 1;
            }

            if (lot[3][i] == lot[2][i] && lot[3][i] != 0) {
                moves.emplace_back(lot[3][i], 3, i);
                lot[2][i] = 0;
                rem_cars -= 1;
            }
        }

        if (rem_cars == 0) break;

        // (2) efectuam o rotatie completa la dreapta
        int starting_id = -1;
        for (int i = 2 * n; i < 4 * n; i++) {
            if (lot[cycle[i].first][cycle[i].second] == 0) {
                starting_id = i; break;
            }
        }

        if (starting_id == -1) {
            std::cout << "-1\n"; return 0;
        }

        for (int i = starting_id; i > starting_id - 2 * n + 1; i--) {
            if (lot[cycle[i - 1].first][cycle[i - 1].second]) {
                moves.emplace_back(lot[cycle[i - 1].first][cycle[i - 1].second], cycle[i].first, cycle[i].second);
                lot[cycle[i].first][cycle[i].second] = lot[cycle[i - 1].first][cycle[i - 1].second];
                lot[cycle[i - 1].first][cycle[i - 1].second] = 0;
            }
        }
    }

    std::cout << moves.size() << "\n";
    for (auto& move: moves) {
        std::cout << move.car_id << " " << move.x + 1 << " " << move.y + 1 << "\n";
    }
    return 0;
}
