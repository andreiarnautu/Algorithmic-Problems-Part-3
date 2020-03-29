/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>

bool check(std::string& s, std::vector<std::pair<char, char>>& ops, int starting_id, int end_id) {
    int q = (int)ops.size();

    for (int i = 0, id = starting_id; i < q; i++) {
        if (ops[i].first == s[id]) {
            if (ops[i].second == 'L') {
                id -= 1;
            } else {
                id += 1;
            }
        }

        if (id == end_id) {
            return true;
        }
    }

    return false;
}


int main() {
    int n, q; std::cin >> n >> q;
    std::string s; std::cin >> s;
    std::vector<std::pair<char, char>> ops(q);
    for (int i = 0; i < q; i++) {
        std::cin >> ops[i].first >> ops[i].second;
    }

    //  Search the left-most character that will end up going out to the right.
    int left, right, left_most = n, right_most = -1;

    left = 0; right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(s, ops, mid, n)) {
            left_most = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    //  Now the right-most one that ends up going out to the left.
    left = 0; right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(s, ops, mid, -1)) {
            right_most = mid; left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    std::cout << left_most - right_most - 1 << '\n';
    return 0;
}
