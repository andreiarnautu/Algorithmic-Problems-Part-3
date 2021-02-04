/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("weightgraph.in");
std::ofstream fout("weightgraph.out");

struct Edge {
    int vertex, index;

    Edge() {}

    Edge(const int _vertex, const int _index) : vertex(_vertex), index(_index) {}
};

int n, m, k;
std::vector<std::vector<Edge > > graph;
std::vector<int> answer, seen;

void read_data() {
    fin >> n >> m >> k;
    graph.resize(n + 1);
    answer = std::vector<int>(m, 0);
    seen = std::vector<int>(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; fin >> u >> v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }
}

void dfs(int node) {
    seen[node] = 1;
    for (auto& edge : graph[node]) {
        if (!seen[edge.vertex] && k > 0) {
            k--;
            answer[edge.index] = 1;
            dfs(edge.vertex);
        }
    }
}

void write_answer() {
    for (auto& x : answer) {
        fout << x << '\n';
    }
}

int main() {
    read_data();
    dfs(1);
    write_answer();
    return 0;
}
