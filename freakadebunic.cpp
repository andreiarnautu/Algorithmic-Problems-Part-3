/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("freakadebunic.in"); std::ofstream fout("freakadebunic.out");

int n, k;
std::vector<int> cnt;
std::vector<std::vector<int>> graph;
std::vector<int> solution;

void read_data() {
    fin >> n >> k;
    cnt.resize(n + 1);
    graph.resize(n + 1);

    for (int i = 0; i < k; i++) {
        int node_id; fin >> node_id;
        cnt[node_id] += 1;
    }

    for (int i = 1; i < n; i++) {
        int u, v; fin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void dfs(int node, int father) {
    for (auto& son : graph[node]) {
        if (son != father) {
            dfs(son, node);
            cnt[node] += cnt[son];
        }
    }

    if (cnt[node] >= 2) {
        solution.push_back(node);
        cnt[node] = 1;
    }
}

int main(int argc, char **argv) {
    read_data();
    dfs(1, 0);

    std::sort(solution.begin(), solution.end());
    fout << solution.size() << "\n";
    for (auto& x : solution) {
        fout << x << " ";
    }
    fout << "\n";
    return 0;
}
