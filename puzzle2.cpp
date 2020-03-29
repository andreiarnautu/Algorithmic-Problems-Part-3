/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("puzzle2.in"); std::ofstream fout("puzzle2.out");

int n, m;
std::vector<int> deg;
std::vector<std::vector<int>> graph;

void solve_one_dimensional(int starting_node) {
    std::vector<int> seen(n + 1, false);
    std::vector<int> ans;

    int node = starting_node, flag = true;
    ans.push_back(node); seen[node] = true;

    while (flag) {
        flag = false;

        for (auto& x: graph[node]) {
            if (!seen[x]) {
                seen[x] = flag = true;
                node = x;
                ans.push_back(node);
            }
        }
    }

    fout << 1 << " " << n << "\n";
    for (auto& node: ans) {
        fout << node << " ";
    }
    fout << "\n";
}

void solve_two_dimensional(int starting_node) {
    std::vector<int> seen(n + 1, false);
    std::vector<int> row = {starting_node};
    seen[starting_node] = true;
    int flag = true, node = starting_node;
    while (flag) {
        flag = true;
        for (auto& x: graph[node]) {
            if (!seen[x] && deg[x] == 2) {
                seen[x] = true;
                row.push_back(x);
                node = x;
                flag = false;
                break;
            }
        }

        if (!flag) break;

        for (auto& x: graph[node]) {
            if (!seen[x] && deg[x] == 3) {
                seen[x] = true;
                row.push_back(x);
                node = x;
                break;
            }
        }
    }

    int c = (int)row.size(), r = n / c;
    fout << r << " " << c << "\n";
    for (int i = 0; i < c; i++) {
        fout << row[i] << " ";
    }
    fout << "\n";

    for (int i = 1; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (auto& x: graph[row[j]]) {
                if (!seen[x]) {
                    seen[x] = true;
                    fout << x << " ";
                    row[j] = x;
                    break;
                }
            }
        }
        fout << "\n";
    }
}

void read_input() {
    fin >> n >> m;
    graph.resize(n + 1);
    deg = std::vector<int>(n + 1, 0);
    for (int i = 0; i < m; i += 1) {
        int u, v; fin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[u] += 1; deg[v] += 1;
    }
}

int main() {
    read_input();

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            solve_one_dimensional(i); return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 2) {
            solve_two_dimensional(i); return 0;
        }
    }

    solve_two_dimensional()

    return 0;
}
