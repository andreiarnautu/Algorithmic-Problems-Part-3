/**
  *  Worg
  */
#include <iostream>

int main() {
    long long answer[2] = {0, 0};
    long long before[2] = {0, 1};

    int n; std::cin >> n;
    for (int i = 0, current = 1; i < n; i++) {
        int x; std::cin >> x;
        if (x < 0) {
            current ^= 1;
        }

        if (current == 1) {
            answer[1] += before[1];
            answer[0] += before[0];
        } else {
            answer[1] += before[0];
            answer[0] += before[1];
        }

        before[current]++;
    }

    std::cout << answer[0] << " " << answer[1] << '\n';
    return 0;
}
