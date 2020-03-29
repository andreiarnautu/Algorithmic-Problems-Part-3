/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("logik.in"); std::ofstream fout("logik.out");

void update_answer(int& answer, int value) {
    if (answer == -1) {
        answer = value;
    } else {
        answer &= value;
    }
}

int main(int argc, char** argv) {
    int n; fin >> n;
    std::vector<int> v(n);
    for (auto& elem : v) {
        fin >> elem;
    }

    int answer = -1;
    for (auto& elem : v) {
        if (elem % 2 == 0) {
            update_answer(answer, elem);
        }
    }

    int odd_before = -1, or_sum = 0;
    for (auto& elem : v) {
        or_sum |= elem;

        if (elem % 2 == 1) {
            if (odd_before != -1) {
                update_answer(answer, or_sum);
            } else {
                odd_before = elem;
            }
            or_sum = elem;
        }
    }

    fout << answer << "\n";

    return 0;
}
