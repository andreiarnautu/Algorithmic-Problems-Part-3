/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int longest_increasing_substring(std::vector<int>& v) {
    std::vector<int> index(v.size(), 0);
    int n = (int)v.size() - 1;

    int size = 0;
    for (int i = 1; i <= n; i++) {
        if (v[i] > v[index[size]]) {
            index[++size] = i;
        } else {
            int left = 1, right = size, pos = 0;

            while (left <= right) {
                int mid = (left + right) / 2;

                if (v[i] <= v[index[mid]]) {
                    pos = mid; right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            index[pos] = i;
        }
    }

    return size;
}

int main() {
    int k1, k2, k3; std::cin >> k1 >> k2 >> k3;
    int n = k1 + k2 + k3;

    std::vector<int> a, b, c;
    for (int i = 0; i < k1; i++) {
        int x; std::cin >> x;
        a.push_back(x);
    }

    for (int i = 0; i < k2; i++) {
        int x; std::cin >> x;
        b.push_back(x);
    }

    for (int i = 0; i < k3; i++) {
        int x; std::cin >> x;
        c.push_back(x);
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());

    std::vector<int> v(1, 0);
    v.insert(v.end(), a.begin(), a.end());
    v.insert(v.end(), b.begin(), b.end());
    v.insert(v.end(), c.begin(), c.end());
    std::cout << n - longest_increasing_substring(v) << "\n";
    return 0;
}
