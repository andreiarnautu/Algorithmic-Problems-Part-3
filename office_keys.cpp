/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

const long long MAX_VALUE = 1e18;

int main() {
    int n, k, p; std::cin >> n >> k >> p;
    std::vector<int> people; people.resize(n);
    for (auto& x: people) {
        std::cin >> x;
    }

    std::vector<int> keys; keys.resize(k);
    for (auto& x: keys) {
        std::cin >> x;
    }

    std::sort(people.begin(), people.end());
    std::sort(keys.begin(), keys.end());

    long long answer = MAX_VALUE;
    for (int i = 0; i + n <= k; i++) {
        long long curr_answer = 0;

        for (int j = 0; j < n; j++) {
            long long person_time = 0;
            person_time += std::abs(people[j] - keys[i + j]);
            person_time += std::abs(keys[i + j] - p);
            curr_answer = std::max(curr_answer, person_time);
        }

        answer = std::min(answer, curr_answer);
    }

    std::cout << answer << "\n";
    return 0;
}
