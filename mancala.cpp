/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

long long Simulate(int id, std::vector<int> a, const int n) {
    int x = a[id];
    a[id] = 0;

    for (int i = 0; i < n; i++) {
        a[i] += x / n;
    }

    x %= n;
    id = (id + 1) % n;
    while (x > 0) {
        a[id]++;
        x--;
        id = (id + 1) % n;
    }

    long long answer = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            answer += a[i];
        }
    }
    return answer;
}

int main() {
    const int n = 14;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    long long answer = 0;
    for (int i = 0; i < n; i++) {
        answer = std::max(answer, Simulate(i, a, n));
    }
    std::cout << answer << '\n';
    return 0;
}
