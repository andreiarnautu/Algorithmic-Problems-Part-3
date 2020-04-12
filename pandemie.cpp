/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("pandemie.in", "r", stdin); FILE *fout = freopen("pandemie.out", "w", stdout);

int n;
std::vector<std::vector<int>> graph;
std::vector<int> dad, virused;

void dfs(int node, int father) {
    dad[node] = father;
    for (auto& nxt : graph[node]) {
        if (nxt != father) {
            dfs(nxt, node);
        }
    }
}

int main(int argc, char **argv) {
    scanf("%d", &n);
    graph.resize(n + 1); dad.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }

    virused = std::vector<int>(n + 1, 0);
    int q; scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int op, x; scanf("%d%d", &op, &x);
        if (op == 1) {
            virused[x] = 1;
        } else if (op == 2) {
            virused[x] = 0;
        } else {
            int node = x;

            while (dad[node]) {
                if (!virused[dad[node]]) {
                    node = dad[node];
                } else {
                    break;
                }
            }
            printf("%d\n", node);
        }
    }
    return 0;
}
