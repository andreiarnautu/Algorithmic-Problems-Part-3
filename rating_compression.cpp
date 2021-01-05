/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

char check_permutation(std::vector<int>& count) {
    for (auto& elem : count) {
        if (elem != 1) {
            return '0';
        }
    }
    return '1';
}

void solve_test() {
    int n; std::cin >> n;
    std::vector<int> a(n), count(n);

    for (auto& elem : a) {
        std::cin >> elem;
        count[--elem]++;
    }

    std::string answer(n, '0');
    answer[0] = check_permutation(count);

    if (count[0]) {
        answer[n - 1] = '1';
        int left = 0, right = n - 1;

        for (int i = n - 1; i > 0; i--) {
            answer[i] = '1';

            int val = n - i - 1;
            if (--count[val] == 0 && (a[left] == val || a[right] == val) && count[val + 1]) {
                if (a[left] == val) {
                    left++;
                } else if (a[right] == val) {
                    right--;
                }
            } else {
                break;
            }
        }
    }

    std::cout << answer << '\n';
}

int main() {
    int test_count; std::cin >> test_count;
    while (test_count) {
        solve_test();
        test_count--;
    }
    return 0;
}


//  1 3 2 -> 1 2 (good!)
