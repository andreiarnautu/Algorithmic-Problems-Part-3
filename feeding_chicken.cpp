/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

void solve_test() {
    int r, c, k; std::cin >> r >> c >> k;
    std::vector<std::vector<int>> farm(r, std::vector<int>(c));

    int total_rice = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            char c; std::cin >> c;
            farm[i][j] = (c == 'R') ? 1 : 0;
            total_rice += farm[i][j];
        }
    }
    std::vector<char> character_list;
    for (char c = '0'; c <= '9'; c++) {
        character_list.push_back(c);
    }
    for (char c = 'a'; c <= 'z'; c++) {
        character_list.push_back(c);
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        character_list.push_back(c);
    }

    std::vector<std::vector<char>> answer(r, std::vector<char>(c));

    int lucky = total_rice % k, char_id = 0;
    int needed = total_rice / k;
    if (lucky) {
        needed += 1;
    }

    for (int i = 0; i < r; i++) {
        int start, add;
        if (i % 2 == 0) {
            start = 0; add = 1;
        } else {
            start = c - 1; add = -1;
        }

        for (int j = start; 0 <= j && j < c; j += add) {
            answer[i][j] = character_list[char_id];
            needed -= farm[i][j];

            if (needed == 0 && char_id + 1 < k) {
                char_id += 1;
                needed = total_rice / k;
                lucky -= 1;

                if (lucky > 0) {
                    needed += 1;
                }
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::cout << answer[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    int test_count; std::cin >> test_count;
    for (int i = 0; i < test_count; i++) {
        solve_test();
    }
    return 0;
}
