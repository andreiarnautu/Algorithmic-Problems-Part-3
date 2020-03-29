/**
  *  Worg
  */
#include <vector>
#include <iostream>

int get_answer(std::vector<int>& v, int n) {
    if (n == 0) {
        return 0;
    }

    int current_cost = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == v.back()) {
            for (int j = i; j + 1 < n - 1; j++) {
                current_cost += 1;
                std::swap(v[j], v[j + 1]);
            }
            break;
        }
    }
    v.pop_back(); v.pop_back();
    return current_cost + get_answer(v, n - 2);
}

int main() {
    int n; std::cin >> n;
    std::vector<int> v(2 * n);
    for (auto& x: v) {
        std::cin >> x;
    }

    std::cout << get_answer(v, 2 * n) << '\n';;
    return 0;
}
