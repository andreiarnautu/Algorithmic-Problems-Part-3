/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("drum7.in");
std::ofstream fout("drum7.out");

int n, k;
std::vector<std::vector<int > > graph;
std::vector<int> count_under, status;

int answer = -2;

void read_data() {
    fin >> n;
    graph.resize(n + 1);
    count_under = status = std::vector<int>(n + 1, 0);

    for (int i = 1; i < n; i++) {
        int u, v; fin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    fin >> k;
    for (int i = 0; i < k; i++) {
        int u; fin >> u;
        count_under[u] = 1;
    }
}

void dfs_1(int node, int dad) {
    bool is_above = false;
    for (int& son : graph[node]) {
        if (son != dad) {
            dfs_1(son, node);
            count_under[node] += count_under[son];

            if (count_under[son] == k) {
                is_above = true;
            }
        }
    }

    if (!is_above && count_under[node] > 0) {
        status[node] = 1;
    }
    answer += status[node] * 2;
}

std::pair<int, int> dfs_2(int node, int dad) {
    std::pair<int, int> best_chain = {0, node};
    for (int& son : graph[node]) {
        if (son != dad && status[son] == 1) {
            std::pair<int, int> aux = dfs_2(son, node);
            aux.first++;
            best_chain = std::max(best_chain, aux);
        }
    }

    return best_chain;
}

int main(int argc, char **argv) {
    read_data();
    dfs_1(1, 0);

    for (int i = 1; i <= n; i++) {
        if (status[i] == 1) {
            std::pair<int, int> aux = dfs_2(i, 0);
            answer -= dfs_2(aux.second, 0).first;
            fout << answer << '\n';
            return 0;
        }
    }
}
