/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_VALUE = 2e5 + 1;

int main() {
    int n, q; std::cin >> n >> q;
    std::vector<int> a(n), first(MAX_VALUE, -1), last(MAX_VALUE, -1), count(MAX_VALUE, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        count[a[i]] += 1;

        if (first[a[i]] == -1) {
            first[a[i]] = i;
        }
        last[a[i]] = i;
    }

    std::vector<std::pair<int, int>> arr;
    for (int i = 0; i < MAX_VALUE; i++) {
        if (first[i] != -1) {
            arr.emplace_back(first[i], i);
        }
    }
    std::sort(arr.begin(), arr.end());

    int answer = n;
    int subtract = 0;
    int current_last = -1;

    for (auto& p: arr) {
        int id = p.second;
        if (first[id] > current_last) {
            answer -= subtract;
            subtract = count[id];
            current_last = last[id];
        } else {
            current_last = std::max(current_last, last[id]);
            subtract = std::max(subtract, count[id]);
        }
    }
    answer -= subtract;
    std::cout << answer << '\n';
    return 0;
}
