/**
  *  Worg
  */
#include <bitset>
#include <string>
#include <vector>
#include <iostream>

const int MAX_N = 75;

std::bitset<MAX_N> masks[MAX_N], universal_mask;
std::vector<int> solution;

void ReadInput(int n) {
    for (int i = 0; i < n; i++) {
        masks[i].reset();
    }

    for (int i = 0; i < n; i++) {
        std::string s; std::cin >> s;
        for (int j = 0; j < n; j++) {
            if (i == j || s[j] == '1') {
                masks[i][j] = 1;
            } else {
                masks[i][j] = 0;
            }
        }
    }
}

int FindNext(std::vector<int> rem) {
    int max_score = 0, index = 0;

    for (int x : rem) {
        int score = 0;
        for (int y : rem) {
            if (masks[x][y] == 1) {
                score++;
            }
        }

        if (score > max_score) {
            max_score = score;
            index = x;
        }
    }

    return index;
}

std::vector<int> FindQuickSolution(int n) {
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }

    std::vector<int> answer;
    while (!v.empty()) {
        int next = FindNext(v);

        answer.push_back(next);

        std::vector<int> new_v;
        for (auto x : v) {
            if (masks[next][x] == 0) {
                new_v.push_back(x);
            }
        }
        v = new_v;
    }

    return answer;
}


void Back(std::vector<int> &arr, std::bitset<MAX_N> mask, int index, int n) {
    if (arr.size() >= solution.size()) {
        return;
    }

    if (mask == universal_mask) {
        solution = arr; return;
    }

    for (int i = index; i < n; i++) {
        arr.push_back(i);

        std::bitset<MAX_N> new_mask = mask;
        new_mask |= masks[i];

        Back(arr, new_mask, i + 1, n);
        arr.pop_back();
    }
}


int main() {
    int n;
    int testcase = 0;

    while (std::cin >> n) {
        testcase++;
        ReadInput(n);

        solution = FindQuickSolution(n);

        for (int i = 0; i < n; i++) {
            universal_mask[i] = 1;
        }
        for (int i = n; i < MAX_N; i++) {
            universal_mask[i] = 0;
        }

        std::vector<int> arr;
        std::bitset<MAX_N> mask; mask.reset();
        Back(arr, mask, 0, n);

        std::cout << "Case " << testcase << ": ";
        std::cout << solution.size() << " ";
        for (auto elem : solution) {
            std::cout << elem + 1 << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
