/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	int n; std::cin >> n;
	std::vector<std::vector<int>> mat(n + 1, std::vector<int>(n + 1));

    int zero_x = -1, zero_y = -1;
	for (int i = 1; i <= n; i++) {
	    for (int j = 1; j <= n; j++) {
		    std::cin >> mat[i][j];

            if (mat[i][j] == 0) {
                mat[i][j] = 10;
                zero_x = i; zero_y = j;
            }
	    }
	}

	std::vector<std::vector<int>> min_twos(n + 1, std::vector<int>(n + 1, 0));
	std::vector<std::vector<int>> min_fives(n + 1, std::vector<int>(n + 1, 0));

    std::vector<std::vector<std::pair<int, int>>> prev_twos(n + 1, std::vector<std::pair<int, int>>(n + 1));
    std::vector<std::vector<std::pair<int, int>>> prev_fives(n + 1, std::vector<std::pair<int, int>>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int left_twos, up_twos, left_fives, up_fives;

            left_twos = up_twos = left_fives = up_fives = n * n;
            if (i > 1) {
                up_twos = min_twos[i - 1][j];
                up_fives = min_fives[i - 1][j];
            }
            if (j > 1) {
                left_twos = min_twos[i][j - 1];
                left_fives = min_fives[i][j - 1];
            }
            min_twos[i][j] = std::min(left_twos, up_twos);
            min_fives[i][j] = std::min(left_fives, up_fives);

            if (left_twos < up_twos) {
                prev_twos[i][j] = std::make_pair(0, -1);
            } else {
                prev_twos[i][j] = std::make_pair(-1, 0);
            }

            if (left_fives < up_fives) {
                prev_fives[i][j] = std::make_pair(0, -1);
            } else {
                prev_fives[i][j] = std::make_pair(-1, 0);
            }

            if (i == 1 && j == 1) {
                min_twos[i][j] = min_fives[i][j] = 0;
                prev_twos[i][j] = prev_fives[i][j] = std::make_pair(-1, -1);
            }

            int x = mat[i][j];
            while (x % 2 == 0) {
                min_twos[i][j] += 1;
                x /= 2;
            }
            while (x % 5 == 0) {
                min_fives[i][j] += 1;
                x /= 5;
            }
        }
    }
    int partial_answer = std::min(min_fives[n][n], min_twos[n][n]);

    //  Daca nu avem raspuns nul, dar exista macar un 0 initial in matrice
    if (partial_answer != 0 && zero_x != -1) {
        std::cout << "1\n";
        int x = 1, y = 1;

        std::string answer;
        while (x < zero_x) {
            answer +=  "D"; x += 1;
        }
        while (y < zero_y) {
            answer +=  "R"; y += 1;
        }

        while (x < n) {
            answer += "D"; x += 1;
        }
        while (y < n) {
            answer += "R"; y += 1;
        }
        std::cout << answer << "\n";
    } else {
        std::string answer;

        int x = n, y = n;
        int flag = 0;

        if (min_fives[n][n] < min_twos[n][n]) {
            flag = 1;
        }

        while (true) {
            int new_x = x;
            int new_y = y;
            if (!flag) {
                if (prev_twos[x][y] == std::make_pair(-1, 0)) {
                    answer += "D";
                } else {
                    answer += "R";
                }
                new_x += prev_twos[x][y].first;
                new_y += prev_twos[x][y].second;

            } else {
                 if (prev_fives[x][y] == std::make_pair(-1, 0)) {
                    answer += "D";
                } else {
                    answer += "R";
                }
                new_x += prev_fives[x][y].first;
                new_y += prev_fives[x][y].second;
            }
            if (new_x == 0 || new_y == 0) {
                answer.pop_back(); break;
            } else {
                x = new_x; y = new_y;
            }
        }

        std::reverse(answer.begin(), answer.end());
        std::cout << partial_answer << "\n" << answer << "\n";
    }
	return 0;
}
