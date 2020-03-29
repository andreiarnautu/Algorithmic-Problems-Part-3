/**
  *  Worg
  */
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_VALUE = 1e6 + 1;

int main() {
    int n; std::cin >> n;
    std::vector<int> count(MAX_VALUE, 0), seen(MAX_VALUE, 0);
    std::vector<std::vector<int>> graph(MAX_VALUE);


    for (int i = 0; i < n; i++) {
        int k; std::cin >> k;
        int last = -1;

        for (int j = 0; j < k; j++) {
            int x; std::cin >> x;
            seen[x] = 1;

            if (last != -1) {
                graph[last].push_back(x);
                count[x] += 1;
            }
            last = x;
        }
    }

    //  Structura de set isi tine mereu elementele sortate.
    //  Astfel, atunci cand extragem un nod, il vom extrage mereu pe primul, fiindca e candidatul valid cu valoarea cea mai mica.

    std::set<int> candidates; //  nodurile asupra carora nu mai exista restrictii
    for (int i = 0; i < MAX_VALUE; i++) {
        if (seen[i] && count[i] == 0) {
            candidates.insert(i);
        }
    }

    std::vector<int> answer;
    while (!candidates.empty()) {
        int node = *candidates.begin();
        candidates.erase(candidates.begin());
        answer.push_back(node);

        for (auto& next_node : graph[node]) {
            count[next_node] -= 1;

            if (count[next_node] == 0) {
                candidates.insert(next_node);
            }
        }
    }

    for (auto& x : answer) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}
