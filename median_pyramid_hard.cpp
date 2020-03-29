#include <vector>
#include <iostream>

int main() {
    int n;

    while (std::cin >> n) {
        std::vector<int> a(2 * n - 1);
        for (auto& x : a) {
            std::cin >> x;
        }

        int left = 1, right = n * 2 - 1, answer = 1;
        while (left <= right) {
            int mid = (left + right) / 2;

            std::vector<bool> v(2 * n - 1);
            for (int i = 0; i < 2 * n - 1; i++) {
                v[i] = a[i] >= mid;
            }

            bool verdict = v[0];
            for (int i = 0; i <= n - 2; i++) {
                if (v[n - 1 - i] == v[n - 2 - i]) {
                    verdict = v[n - 1 - i]; break;
                }
                if (v[n - 1 + i] == v[n + i]) {
                    verdict = v[n - 1 + i]; break;
                }
            }

            if (verdict) {
                answer = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        std::cout << answer << '\n';
    }
    
    return 0;
}
