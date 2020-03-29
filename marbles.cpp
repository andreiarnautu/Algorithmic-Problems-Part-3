/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_VAL = 20;
const long long MAX_INF = 1LL << 61;


std::vector<std::vector<long long>> ComputeAdd(int n, std::vector<int> v) {
    std::vector<std::vector<long long>> add(MAX_VAL, std::vector<long long>(MAX_VAL, 0));

    std::vector<int> count(MAX_VAL, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < MAX_VAL; j++) {
            add[j][v[i]] += count[j];
        }
        count[v[i]] += 1;
    }

    return add;
}

long long IntervalSum(long long start, long long count) {
    return start * count + count * (count - 1) / 2;
}

int main() {
    int n; std::cin >> n;
    std::vector<int> v(n);
    std::vector<long long> sum_pos(MAX_VAL, 0), how_many(MAX_VAL, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
        v[i] -= 1;
        sum_pos[v[i]] += i;
        how_many[v[i]] += 1;
    }

    std::vector<std::vector<long long>> add = ComputeAdd(n, v);

    std::vector<long long> dp(1 << MAX_VAL, MAX_INF);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << MAX_VAL); mask++) {
        for (int i = 0; i < MAX_VAL; i++) {
            if (!(mask & (1 << i))) {
                long long result = sum_pos[i];
                long long start = 0;

                for (int j = 0; j < MAX_VAL; j++) {
                    if (mask & (1 << j)) {
                        result += add[i][j];
                        start += how_many[j];
                    }
                }

                result -= IntervalSum(start, how_many[i]);
                dp[mask ^ (1 << i)] = std::min(dp[mask ^ (1 << i)], dp[mask] + result);
            }
        }
    }

    std::cout << dp[(1 << MAX_VAL) - 1] << '\n';
    return 0;
}
