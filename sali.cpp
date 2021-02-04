/**
  *  Worg
  */
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("sali.in");
std::ofstream fout("sali.out");

int n, m;
std::vector<std::vector<int> > graph;
std::vector<int> visited, component, answer;
int range_start = 1;

void read_data() {
    fin >> n >> m;
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v; fin >> u >> v;
        u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void dfs_component(int node) {
    visited[node] = true;
    component.push_back(node);

    for (int& next : graph[node]) {
        if (!visited[next]) {
            dfs_component(next);
        }
    }
}

int get_bfs_distance(int start_node) {
    std::vector<int> bfs_dist(n, 0);
    std::queue<int> queue;
    int max_dist = 1;

    bfs_dist[start_node] = 1;
    queue.push(start_node);
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();
        max_dist = std::max(max_dist, bfs_dist[node]);

        for (int& next : graph[node]) {
            if (!bfs_dist[next]) {
                bfs_dist[next] = bfs_dist[node] + 1;
                queue.push(next);
            }
        }
    }

    return max_dist;
}

std::pair<int, int> get_start_node() {
    std::pair<int, int> start = {-1, -1};

    for (int& node : component) {
        int bfs_distance = get_bfs_distance(node);
        start = std::max(start, {bfs_distance, node});
    }

    return start;
}

void paint_component(int start_node) {
    std::vector<int> bfs_dist(n, 0);
    std::queue<int> queue;

    answer[start_node] = range_start;
    queue.push(start_node);
    while (!queue.empty()) {
        int node = queue.front();
        queue.pop();

        for (int& next : graph[node]) {
            if (!answer[next]) {
                answer[next] = answer[node] + 1;
                queue.push(next);
            }
        }
    }
}

void build_answer() {
    visited = std::vector<int>(n, 0);
    answer = std::vector<int>(n, 0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_component(i);
            std::pair<int, int> start = get_start_node();
            paint_component(start.second);

            range_start += start.first;
            component.clear();
        }
    }
}

void print_answer() {
    fout << range_start - 1 << '\n';
    for (int& x : answer) {
        fout << x << ' ';
    }
}

int main(int argc, char **argv) {
    read_data();
    build_answer();
    print_answer();
    return 0;
}
