/**
  *  Worg
  */
#include <set>
#include <vector>
#include <iostream>

int main(int argc, char const *argv[]) {
    int n, k; std::cin >> n >> k;
    std::vector<long long> costs(n), final_time(n);
    for (auto& c : costs) {
        std::cin >> c;
    }

    std::set<std::pair<long long, int>> available;
    for (int i = 0; i < k + n; i++) {
        if (i < n) {
            available.emplace(costs[i], i);
        }

        if (i >= k) {
            std::pair<long long, int> best = *available.rbegin();
            final_time[best.second] = i;
            available.erase(std::prev(available.end()));
        }
    }

    long long final_cost = 0;
    for (int i = 0; i < n; i++) {
        final_cost += costs[i] * (final_time[i] - i);
    }

    std::cout << final_cost << '\n';
    for (auto& time: final_time) {
        std::cout << time + 1 << " ";
    }
    std::cout << '\n';

    return 0;
}
