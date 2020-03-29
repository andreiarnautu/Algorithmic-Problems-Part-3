/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


const int TETA = 26;

std::vector<int> fix(std::vector<int> f) {
    std::vector<int> odd;
    for (int i = 0; i < TETA; i++) {
        if (f[i] % 2 == 1) {
            odd.push_back(i);
        }
    }

    for (int left = 0, right = odd.size() - 1; left <= right; left++, right--) {
        f[odd[left]] += 1;
        f[odd[right]] -= 1;
    }

    return f;
}

int main(int argc, char* argv[]) {
    std::string s; std::cin >> s;
    std::vector<int> f(TETA, 0);
    for (int i = 0; i < (int)s.size(); i++) {
        f[s[i] - 'a'] += 1;
    }

    f = fix(f);

    std::string answer; answer.resize(s.size());
    for (int id = 0, left = 0, right = (int)answer.size() - 1; left <= right; left++, right--) {
        if (left == right) {
            for (int i = 0; i < TETA; i++) {
                if (f[i] == 1) {
                    answer[left] = ('a' + i);
                }
            }
        } else {
            while (id < TETA && f[id] < 2) {
                id += 1;
            }
            answer[left] = answer[right] = ('a' + id);
            f[id] -= 2;
        }
    }

    std::cout << answer << "\n";
    return 0;
}
