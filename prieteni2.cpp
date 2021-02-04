/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("prieteni2.in");
std::ofstream fout("prieteni2.out");

struct Node {
    int size;
    int best, best_left, best_right;

    Node() : best(0), best_left(0), best_right(0) {}
};

int n, q;
std::vector<Node> stree;
std::vector<int> query_nodes;

void build_tree(int node, int left, int right) {
    if (left == right) {
        stree[node].size = 1;
        return;
    }

    int mid = (left + right) >> 1, left_son = node << 1, right_son = left_son + 1;

    build_tree(left_son, left, mid);
    build_tree(right_son, mid + 1, right);
    stree[node].size = stree[left_son].size + stree[right_son].size;
}

void update(int node, int left, int right, int index, int value) {
    if (left == right) {
        stree[node].best = stree[node].best_left = stree[node].best_right = value;
        return;
    }

    int mid = (left + right) >> 1, left_son = node << 1, right_son = left_son + 1;

    if (index <= mid) {
        update(left_son, left, mid, index, value);
    } else {
        update(right_son, mid + 1, right, index, value);
    }

    stree[node].best = std::max(stree[left_son].best, stree[right_son].best);
    stree[node].best = std::max(stree[node].best, stree[left_son].best_right + stree[right_son].best_left);

    stree[node].best_left = stree[left_son].best_left;
    if (stree[left_son].best_left == stree[left_son].size) {
        stree[node].best_left += stree[right_son].best_left;
    }

    stree[node].best_right = stree[right_son].best_right;
    if (stree[right_son].best_right == stree[right_son].size) {
        stree[node].best_right += stree[left_son].best_right;
    }
}

void query(int node, int left, int right, int first, int last) {
    if (first <= left && right <= last) {
        query_nodes.push_back(node);
        return;
    }

    int mid = (left + right) >> 1, left_son = node << 1, right_son = left_son + 1;

    if (first <= mid) {
        query(left_son, left, mid, first, last);
    }
    if (mid < last) {
        query(right_son, mid + 1, right, first, last);
    }
}

int solve_query(int a, int b) {
    query(1, 1, n - 1, a, b - 1);

    //  left to right
    int answer = 0, prev_consec = 0;
    for (auto& node : query_nodes) {
        answer = std::max(answer, prev_consec + stree[node].best_left);
        answer = std::max(answer, stree[node].best);

        if (stree[node].best == stree[node].size) {
            prev_consec += stree[node].size;
        } else {
            prev_consec = stree[node].best_right;
        }
    }

    //  right to left
    std::reverse(query_nodes.begin(), query_nodes.end());
    prev_consec = 0;
    for (auto& node : query_nodes) {
        answer = std::max(answer, prev_consec + stree[node].best_right);
        answer = std::max(answer, stree[node].best);

        if (stree[node].best == stree[node].size) {
            prev_consec += stree[node].size;
        } else {
            prev_consec = stree[node].best_left;
        }
    }

    query_nodes.clear();
    return answer + 1;
}

int main() {
    fin >> n >> q;
    stree = std::vector<Node>(n * 4);
    build_tree(1, 1, n - 1);

    for (int i = 0; i < q; i++) {
        int event; fin >> event;

        if (event == 1) {
            int x; fin >> x;
            update(1, 1, n - 1, x, 1);
        } else if (event == 2) {
            int x; fin >> x;
            update(1, 1, n - 1, x, 0);
        } else {
            int a, b; fin >> a >> b;
            fout << solve_query(a, b) << '\n';
        }
    }

    return 0;
}
