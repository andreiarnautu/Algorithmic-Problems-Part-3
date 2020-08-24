/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>
std::ifstream fin("mit.in"); std::ofstream fout("mit.out");

std::vector<int> stree, lazy;

void build_tree(int node, int left, int right) {
    if (left == right) {
        fin >> stree[node];
        return;
    }

    int mid = (left + right) >> 1, left_son = node << 1, right_son = left_son + 1;
    build_tree(left_son, left, mid);
    build_tree(right_son, mid + 1, right);

    stree[node] = std::max(stree[left_son], stree[right_son]);
}

void propagate(int node, int left, int right) {
    int left_son = node << 1, right_son = left_son + 1;

    stree[node] += lazy[node];
    if (left != right) {
        lazy[left_son] += lazy[node];
        lazy[right_son] += lazy[node];
    }
    lazy[node] = 0;
}

void query_tree(int node, int left, int right, int first, int last, int &query_answer) {
    int mid = (left + right) >> 1, left_son = node << 1, right_son = left_son + 1;

    propagate(node, left, right);

    if (first <= left && right <= last) {
        if (left != right) {
            propagate(left_son, left, mid);
            propagate(right_son, mid + 1, right);
            stree[node] = std::max(stree[left_son], stree[right_son]);
        }
        query_answer = std::max(query_answer, stree[node]);
        return;
    }

    if (first <= mid) {
        query_tree(left_son, left, mid, first, last, query_answer);
    }
    if (mid < last) {
        query_tree(right_son, mid + 1, right, first, last, query_answer);
    }

    if (left != right) {
        propagate(left_son, left, mid);
        propagate(right_son, mid + 1, right);
        stree[node] = std::max(stree[node], std::max(stree[left_son], stree[right_son]));
    }
}

void update_tree(int node, int left, int right, int first, int last, int value) {
    int mid = (left + right) >> 1, left_son = node << 1, right_son = left_son + 1;

    //  Propagate
    propagate(node, left, right);

    if (first <= left && right <= last) {
        lazy[node] += value;
        return;
    }

    if (first <= mid) {
        update_tree(left_son, left, mid, first, last, value);
    }
    if (mid < last) {
        update_tree(right_son, mid + 1, right, first, last, value);
    }

    propagate(left_son, left, mid);
    propagate(right_son, mid + 1, right);
    stree[node] = std::max(stree[left_son], stree[right_son]);
}

int main(int argc, char **argv) {
    int n, t; fin >> n >> t;

    stree = lazy = std::vector<int>(4 * n, 0);
    build_tree(1, 1, n);

    for (int i = 0; i < t; i++) {
        int type, a, b; fin >> type >> a >> b;

        if (type == 1) {
            int query_answer = 0;
            query_tree(1, 1, n, a, b, query_answer);
            fout << query_answer << '\n';
        } else {
            int value; fin >> value;
            update_tree(1, 1, n, a, b, value);
        }
    }
    return 0;
}
