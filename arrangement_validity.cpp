/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

struct stree_node {
    int min_value, lazy_add;

    stree_node() : min_value(0), lazy_add(0) {

    }
};

void build_stree(int node, int left, int right, std::vector<stree_node> &stree, std::vector<int> &v) {
    if (left == right) {
        stree[node].min_value = v[left];
        stree[node].lazy_add = 0;
        return;
    }

    int mid = (left + right) / 2, left_son = node * 2, right_son = left_son + 1;

    build_stree(left_son, left, mid, stree, v);
    build_stree(right_son, mid + 1, right, stree, v);

    stree[node].min_value = std::min(stree[left_son].min_value, stree[right_son].min_value);
    stree[node].lazy_add = 0;
}

int update(int node, int left, int right, int value, std::vector<stree_node> &stree, std::vector<int> &sol) {
    //  Lazy Update
    int mid = (left + right) / 2, left_son = node * 2, right_son = left_son + 1;
    if (left != right) {
        stree[left_son].min_value += stree[node].lazy_add;
        stree[left_son].lazy_add += stree[node].lazy_add;

        stree[right_son].min_value += stree[node].lazy_add;
        stree[right_son].lazy_add += stree[node].lazy_add;

        stree[node].lazy_add = 0;
    }
    //  Done

    if (left == right) {
        sol[left] = value;
        stree[node].min_value = (int)stree.size();
        return left;
    }

    int return_value;
    if (stree[right_son].min_value <= stree[left_son].min_value) {
        return_value = update(right_son, mid + 1, right, value, stree, sol);
    } else {
        return_value = update(left_son, left, mid, value, stree, sol);
    }

    stree[node].min_value = std::min(stree[left_son].min_value, stree[right_son].min_value);
    return return_value;
}


void decrease(int node, int left, int right, int first, int last, std::vector<stree_node> &stree) {
    //  Lazy Update
    if (first > last) return;

    int mid = (left + right) / 2, left_son = node * 2, right_son = left_son + 1;
    if (left != right) {
        stree[left_son].min_value += stree[node].lazy_add;
        stree[left_son].lazy_add += stree[node].lazy_add;

        stree[right_son].min_value += stree[node].lazy_add;
        stree[right_son].lazy_add += stree[node].lazy_add;

        stree[node].lazy_add = 0;
    }
    //  Done

    if (first <= left && right <= last) {
        stree[node].min_value -= 1;
        stree[node].lazy_add -= 1;
        return;
    }

    if (first <= mid) {
        decrease(left_son, left, mid, first, last, stree);
    }
    if (mid + 1 <= last) {
        decrease(right_son, mid + 1, right, first, last, stree);
    }


    stree[node].min_value = std::min(stree[left_son].min_value, stree[right_son].min_value);
}


void solve_test() {
    int n; std::cin >> n;
    std::vector<int> v(n);

    bool flag = false;
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
        if (v[i] > i) {
            flag = true;
        }
    }
    if (flag) {
        std::cout << "-1\n"; return;
    }

    std::vector<stree_node> stree(4 * n);
    build_stree(1, 0, n - 1, stree, v);

    std::vector<int> sol(n, 0);
    for (int step = n; step >= 1; step--) {
        int where = update(1, 0, n - 1, step, stree, sol);
        //std::cout << "where = " << where << "\n";
        decrease(1, 0, n - 1, where + 1, n - 1, stree);
    }

    for (int i = 0; i < n; i++) {
        std::cout << sol[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    int test_count; std::cin >> test_count;

    for (int i = 0; i < test_count; i++) {
        std::cout << "Test : " << i + 1 << "\n";
        solve_test();
    }
    return 0;
}
