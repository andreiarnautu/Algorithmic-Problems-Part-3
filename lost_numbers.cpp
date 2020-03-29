/**
  *  Worg
  */
#include <map>
#include <vector>
#include <iostream>

const std::vector<int> candidates = {4, 8, 15, 16, 23, 42};

int ask(int i, int j) {
    std::cout << "? " << i << " " << j << '\n';
    std::cout.flush();
    int verdict; std::cin >> verdict;
    return verdict;
}

std::vector<int> find_three(int start) {
    int verdict_1 = ask(start, start + 1);
    int verdict_2 = ask(start, start + 2);

    std::map<int, int> my_map;

    for (int i = 0; i < (int) candidates.size(); i++) {
        for (int j = i + 1; j < (int) candidates.size(); j++) {
            int p = candidates[i] * candidates[j];

            if (verdict_1 == p || verdict_2 == p) {
                my_map[candidates[i]] += 1;
                my_map[candidates[j]] += 1;
            }
        }
    }

    std::vector<int> ret;
    int a = 0;
    for (int x: candidates) {
        if (my_map[x] == 2) {
            a = x; break;
        }
    }

    ret.push_back(a);
    ret.push_back(verdict_1 / a);
    ret.push_back(verdict_2 / a);
    return ret;
}

void add(std::vector<int>& a, std::vector<int> b) {
    for(int x: b) {
        a.push_back(x);
    }
}

int main(int argc, char const *argv[]) {
    std::vector<int> answer;
    add(answer, find_three(1));
    add(answer, find_three(4));

    std::cout << "! ";
    for (int x: answer) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    std::cout.flush();
    return 0;
}
