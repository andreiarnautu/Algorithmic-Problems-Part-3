/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("rusuoaica.in"); std::ofstream fout("rusuoaica.out");

struct Edge {
    int u, v, c;

    Edge() {}

    Edge(const int _u, const int _v, const int _c) : u(_u), v(_v), c(_c) {}

    bool operator <(const Edge &other) const {
        if (this->c != other.c) {
            return this->c < other.c;
        } else if (this->u != other.u) {
            return this->u < other.u;
        }
        return this->v < other.v;
    }
};

int group(std::vector<int>& father, int x) {
    if (x != father[x]) {
        father[x] = group(father, father[x]);
    }
    return father[x];
}

void unite(std::vector<int>& father, int u, int v) {
    father[group(father, v)] = group(father, u);
}

int main(int argc, char** argv) {
    int n, m, a; fin >> n >> m >> a;
    std::vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v, c; fin >> u >> v >> c;
        edges.emplace_back(u - 1, v - 1, c);
    }

    std::sort(edges.begin(), edges.end());

    std::vector<int> father(n);
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }

    int total_cost = 0, edges_selected = 0;
    for (auto& edge : edges) {
        if (group(father, edge.u) != group(father, edge.v)) {
            unite(father, edge.u, edge.v);
            edges_selected += 1;

            if (edge.c <= a) {
                total_cost += edge.c;
            } else {
                total_cost += (a - edge.c);
            }
        } else {
            total_cost -= edge.c;
        }
    }

    total_cost += a * (n - 1 - edges_selected);
    fout << total_cost << "\n";
    return 0;
}
