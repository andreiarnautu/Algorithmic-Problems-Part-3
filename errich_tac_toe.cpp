/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char **argv) {
    int tests; std::cin >> tests;

    while (tests) {
        int n; std::cin >> n;
        std::vector<std::string> table(n);
        int count[3][2] = {{0, 0}, {0, 0}, {0, 0}};
        
        int k = 0;
        for (int i = 0; i < n; i++) {
            std::cin >> table[i];
            for (int j = 0; j < n; j++) {
                int val = (i + j) % 3;

                if (table[i][j] == 'X') {
                    count[val][0] += 1;
                    k += 1;
                } else if (table[i][j] == 'O') {
                    count[val][1] += 1;
                    k += 1;
                }
            }
        }
        
        //  Set the diagonals for swapping Xs and Ys
        bool found_sol = false;
        for (int d1 = 0; d1 < 3; d1++) {
            for (int d2 = 0; d2 < 3; d2++) {
                if (d1 == d2 || found_sol) continue;

                if (count[d1][0] + count[d2][1] <= k / 3) {
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            if ((i + j) % 3 == d1 && table[i][j] == 'X') {
                                table[i][j] = 'O';
                            } else if ((i + j) % 3 == d2 && table[i][j] == 'O') {
                                table[i][j] = 'X';
                            }
                        }
                        std::cout << table[i] << '\n';
                    }
                    found_sol = true;
                }
            }
        }
        tests--;
    }
    return 0;
}
