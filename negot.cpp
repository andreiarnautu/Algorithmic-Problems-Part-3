/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("negot.in"); std::ofstream fout("negot.out");

int n, m, k;
int match_count;
std::vector<std::vector<int>> graph;

std::vector<bool> checked;
std::vector<int> left, right;

void read_input() {
    fin >> n >> m >> k;

    graph.resize(n * k);
    for (int i = 0; i < n; i++) {
        int counter; fin >> counter;

        for (int j = 0; j < counter; j++) {
            int shop_id; fin >> shop_id;
            for (int it = 0; it < k; it++) {
                graph[i * k + it].push_back(shop_id - 1);
            }
        }
    }
}


bool pair_up(int node) {
    if (checked[node]) return false;
    checked[node] = true;

    for (auto& nxt : graph[node]) {
        if (right[nxt] == -1) {
            left[node] = nxt; right[nxt] = node;
            match_count += 1;
            return true;
        }
    }

    for (auto& nxt : graph[node]) {
        if (pair_up(right[nxt])) {
            left[node] = nxt; right[nxt] = node;
            return true;
        }
    }

    return false;
}


void hopcroft_carp() {
    checked.resize(n * k);
    left = std::vector<int>(n * k, -1);
    right = std::vector<int>(m, -1);

    bool flag;
    do {
        for (int i = 0; i < n * k; i++) {
            checked[i] = false;
        }

        flag = false;
        for (int i = 0; i < n * k; i++) {
            if (left[i] == -1) {
                flag |= pair_up(i);
            }
        }
    } while (flag);
}


int main(int argc, char **argv) {
    read_input();
    hopcroft_carp();
    fout << match_count << "\n";
    return 0;
}
