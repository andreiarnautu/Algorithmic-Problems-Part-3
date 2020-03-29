/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main(int argc, char const *argv[]) {
    int n; std::cin >> n;
    std::vector<int> sticks(n);
    for (int& num : sticks) {
        std::cin >> num;
    }

    std::sort(sticks.begin(), sticks.end());

    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int sum = sticks[i] + sticks[j];

            if (sum > sticks.back()) {
                answer += n - j - 1;
            } else {
                int left = j + 1, right = n - 1, index = j;

                while (left <= right) {
                    int mid = (left + right) / 2;

                    if (sticks[mid] < sum) {
                        index = mid; left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }

                answer += index - j;
            }
        }
    }

    std::cout << answer << '\n';
    return 0;
}
