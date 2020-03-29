/**
  *  Worg
  */
#include <queue>
#include <bitset>
#include <vector>
#include <iostream>

const int MAX_N = 7000;

std::bitset<MAX_N> cool[MAX_N];

void Compute(const int& n, const std::vector<long long>& a, std::vector<long long>& cool_count) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long mask = a[i] & a[j];

            if (mask != a[i]) {
                cool[i][j] = 1;
                cool_count[i] += 1;
            }
        }
    }
}

int main() {
    int n; std::cin >> n;
    std::vector<long long> a(n), b(n), cool_count(n, 0);

    for (auto& elem: a) {
        std::cin >> elem;
    }
    for (auto& elem: b) {
        std::cin >> elem;
    }

    Compute(n, a, cool_count);

    std::queue<int> q;
    int rem = n;
    for (int i = 0; i < n; i++) {
        if (cool_count[i] == rem - 1) {
            b[i] = 0; q.push(i);
        }
    }

    while (!q.empty()) {
        int id = q.front(); q.pop();
        rem--;

        for (int i = 0; i < n; i++) {
            if (cool[i][id] == 1) {
                cool_count[i]--;
            }
        }

        for (int i = 0; i < n; i++) {
            if (cool_count[i] == rem - 1 && b[i] != 0) {
                q.push(i); b[i] = 0;
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += b[i];
    }
    std::cout << ans << '\n';

    return 0;
}
