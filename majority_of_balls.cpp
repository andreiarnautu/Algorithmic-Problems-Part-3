/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int n;

bool get_verdict(std::vector<int>& a) {
    std::cout << "? ";
    for (auto& x: a) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::string verdict; std::cin >> verdict;
    return verdict == "Red";
}

bool ask(int start) {
    std::vector<int> a;
    for (int i = start; i < start + n; i++) {
        a.push_back(i);
    }
    return get_verdict(a);
}


int main() {
    std::cin >> n;
    int l = ask(1);

    int left = 1, right = n + 1, critical = 1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (ask(mid) == l) {
            critical = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    std::vector<int> answer(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        std::vector<int> a = {i};

        if (i < critical || i >= critical + n) {
            for (int j = critical + 1; j < critical + n; j++) {
                a.push_back(j);
            }

            answer[i] = get_verdict(a);
        } else {
            for (int j = 1; j < critical; j++) {
                a.push_back(j);
            }
            for (int j = critical + n + 1; j <= 2 * n; j++) {
                a.push_back(j);
            }

            answer[i] = get_verdict(a);
        }
    }

    std::cout << "! ";
    for (int i = 1; i <= 2 * n; i++) {
        if (answer[i]) {
            std::cout << "R";
        } else {
            std::cout << "B";
        }
    }
    std::cout << std::endl;
    return 0;
}
