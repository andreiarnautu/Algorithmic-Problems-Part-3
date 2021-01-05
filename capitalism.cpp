/**
  *  Worg
  */
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const int MAX_N = 200 + 1;
const int MAX_M = 2000 + 1;
const int MAX_INF = 1e9;

struct Edge {
    int u, v, b;

    Edge() : u(0), v(0), b(0) {}

    Edge(const int _u, const int _v, const int _b) : u(_u), v(_v), b(_b) {}
};

int n, m;
int dist[MAX_N][MAX_N];
Edge edges[MAX_M];

void read_data() {
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = (i != j ? MAX_INF : 0);
        }
    }

    for (int i = 0; i < m; i++) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].b;
        dist[edges[i].u][edges[i].v] = 1;
        dist[edges[i].v][edges[i].u] = (edges[i].b == 0 ? 1 : -1);
    }

}

void floyd_warshall() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != MAX_INF && dist[k][j] != MAX_INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    if (dist[i][j] < -MAX_INF) {
                        std::cout << "NO\n";
                        exit(0);
                    }
                }
            }
        }
    }
}

void print_solution() {
    int max_dist = -1, start_node = 1;
    for (int i = 1; i <= n; i++) {
        if (dist[i][i] < 0) {
            std::cout << "NO\n";
            exit(0);
        }

        for (int j = 1; j <= n; j++) {
            if (max_dist < dist[i][j]) {
                max_dist = dist[i][j];
                start_node = i;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (dist[start_node][edges[i].u] == dist[start_node][edges[i].v]) {
            std::cout << "NO\n";
            exit(0);
        }
    }

    std::cout << "YES\n" << max_dist << '\n';
    for (int i = 1; i <= n; i++) {
        std::cout << dist[start_node][i] << " ";
    }
    std::cout << '\n';
}

int main() {
    read_data();
    floyd_warshall();
    print_solution();
    return 0;
}
