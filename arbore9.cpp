/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("arbore9.in");
std::ofstream fout("arbore9.out");

struct Edge {
    int vertex;
    long long cost_forward, cost_backward;

    Edge() {}

    Edge(const int _vertex, const long long _cost_forward, const long long _cost_backward) :
        vertex(_vertex),
        cost_forward(_cost_forward),
        cost_backward(_cost_backward)
    {}
};

const long long INF = 1e18;

//  naming: yes = you come back to the node, no = you don't
int n;
std::vector<std::vector<Edge > > graph;
std::vector<long long> down_yes, down_no, answer;

void read_data() {
    fin >> n;
    graph.resize(n + 1);
    down_yes = down_no = answer = std::vector<long long>(n + 1, 0);

    for (int i = 1; i < n; i++) {
        int u, v, a, b; fin >> u >> v >> a >> b;
        graph[u].emplace_back(v, a, b);
        graph[v].emplace_back(u, b, a);
    }
}

void dfs_1(int node, int dad) {
    long long best_upgrade_down = 0;

    for (Edge& edge : graph[node]) {
        if (edge.vertex != dad) {
            dfs_1(edge.vertex, node);
            down_yes[node] += std::max(0LL, down_yes[edge.vertex] + edge.cost_backward);
            best_upgrade_down = std::max(best_upgrade_down,
                    std::max(0LL, edge.cost_forward + down_no[edge.vertex]) - std::max(0LL, edge.cost_backward + down_yes[edge.vertex]));
        }
    }

    down_no[node] = down_yes[node] + best_upgrade_down;
}

void dfs_2(int node, int dad, long long up_yes, long long up_no) {
    answer[node] = std::max(down_yes[node] + up_no, down_no[node] + up_yes);

    std::pair<long long, long long> best_down = {-INF, -INF};
    int best_id = -1;

    for (Edge& edge : graph[node]) {
        if (edge.vertex != dad) {
            long long aux = std::max(0LL, edge.cost_forward + down_no[edge.vertex]) -
                            std::max(0LL, edge.cost_backward + down_yes[edge.vertex]);

            if (aux > best_down.first) {
                best_id = edge.vertex;
                best_down.second = best_down.first;
                best_down.first = aux;
            } else if (aux > best_down.second) {
                best_down.second = aux;
            }
        }
    }

    for (Edge& edge : graph[node]) {
        if (edge.vertex != dad) {
            long long son_sum = down_yes[node] - std::max(0LL, edge.cost_backward + down_yes[edge.vertex]);
            long long new_up_yes = std::max(0LL, up_yes + edge.cost_forward + son_sum);
            if (edge.vertex == best_id) {
                long long new_up_no = std::max(0LL, std::max(up_no + edge.cost_backward + son_sum,
                                        up_yes + son_sum + edge.cost_backward + std::max(0LL, best_down.second)));
                dfs_2(edge.vertex, node, new_up_yes, new_up_no);
            } else {
                long long new_up_no = std::max(0LL, std::max(up_no + edge.cost_backward + son_sum,
                                        up_yes + son_sum + edge.cost_backward + std::max(0LL, best_down.first)));
                dfs_2(edge.vertex, node, new_up_yes, new_up_no);
            }
        }
    }
}

void print_answer() {
    for (int i = 1; i <= n; i++) {
        fout << answer[i] << " ";
    }
}

int main(int argc, char **argv) {
    read_data();
    dfs_1(1, 0);
    dfs_2(1, 0, 0, 0);
    print_answer();
    return 0;
}
