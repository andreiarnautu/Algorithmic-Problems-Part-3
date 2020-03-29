/**
  *  Worg
  */
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

const int max_elem = 9;
const int max_mask = 1 << 9;
const int inf = 2e9 + 1;

int cnt[max_mask];
int min_cost[max_mask];
int prev[max_mask];

int main() {
    int n, m; std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        int mask = 0;

        for (int j = 0; j < k; j++) {
            int x; std::cin >> x; x--;
            mask ^= (1 << x);
        }

        for (int j = 0; j < max_mask; j++) {
            if ((j & mask) == mask) {
                cnt[j]++;
            }
        }
    }

    for (int i = 0; i < max_mask; i++) {
        min_cost[i] = inf;
    }

    std::vector<int> costs(m), masks(m);
    for (int i = 0; i < m; i++) {
        int cost, k; std::cin >> cost >> k;
        int mask = 0;

        for (int j = 0; j < k ; j++) {
            int x; std::cin >> x; x--;
            mask ^= (1 << x);
        }

        costs[i] = cost; masks[i] = mask;
        if (min_cost[mask] > cost) {
            min_cost[mask] = cost;
            prev[mask] = i;
        }
    }

    int max_pleased = -1, cost = inf, id1 = -1, id2 = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < max_mask; j++) {
            if (min_cost[j] == inf || prev[j] == i) continue;

            int pleased_here = cnt[j | masks[i]];
            int cost_here = min_cost[j] + costs[i];

            if (pleased_here > max_pleased || (pleased_here == max_pleased && cost_here < cost)) {
                max_pleased = pleased_here;
                cost = cost_here;
                id1 = prev[j];
                id2 = i;
            }
        }
    }

    //std::cout << "max_pleased = " << max_pleased << "; cost = " << cost << '\n';
    std::cout << id1 + 1 << " " << id2 + 1 << '\n';
    return 0;
}
