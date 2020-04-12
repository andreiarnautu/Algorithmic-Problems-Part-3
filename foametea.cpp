/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("foametea.in", "r", stdin); FILE *fout = freopen("foametea.out", "w", stdout);

const int INF = 1e9;

struct NodeDist {
    int dist, vertex, food;

    NodeDist(int _dist, int _vertex, int _food = 0) : dist(_dist), vertex(_vertex), food(_food) {}

    bool operator <(const NodeDist &other) const {
        if (this->dist != other.dist) {
            return this->dist > other.dist;
        }
        return this->vertex < other.vertex;
    }
};
/*-------- Data --------*/
int n, m, k;
std::vector<int> sarmale, dist;
std::vector<std::vector<NodeDist>> graph;
/*-------- --------*/

std::pair<int, int> get_old_node_id(int curr_id) {
    return std::make_pair(curr_id / (k + 1), curr_id % (k + 1));
}

int get_new_node_id(int curr_id, int s) {
    return curr_id * (k + 1) + s;
}


void read_data() {
    scanf("%d%d%d", &n, &m, &k);

    sarmale.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &sarmale[i]);
    }

    graph.resize((n + 2) * (k + 2));
    dist = std::vector<int>((n + 2) * (k + 2), INF);
    for (int i = 1; i <= m; i++) {
        int a, b, len, c; scanf("%d%d%d%d", &a, &b, &len, &c);

        for (int food_start = c; food_start <= k; food_start++) {
            int dist = len * ((food_start - c) * (food_start - c) + 1);
            graph[get_new_node_id(a, food_start)].emplace_back(dist, get_new_node_id(b, food_start - c), food_start - c);
        }
    }
}

void run_dijkstra() {
    std::priority_queue<NodeDist> pq;

    pq.emplace(0, get_new_node_id(1, 0));

    while(!pq.empty()) {
        NodeDist pq_node = pq.top(); pq.pop();

        if (dist[pq_node.vertex] != INF) continue;

        int node = get_old_node_id(pq_node.vertex).first, food = get_old_node_id(pq_node.vertex).second;
        int node_distance = pq_node.dist;
        dist[pq_node.vertex] = node_distance;

        if (node == n) {
            printf("%d\n", node_distance); return;
        }

        for (int curr_food = food; curr_food <= std::min(k, food + sarmale[node]); curr_food++) {
            for (auto& nxt : graph[get_new_node_id(node, curr_food)]) {
                if (dist[nxt.vertex] == INF) {
                    pq.emplace(node_distance + nxt.dist, nxt.vertex);
                }
            }
        }
    }

    printf("Fomistul moare de foame\n");
}

int main(int argc, char **argv) {
    read_data();
    run_dijkstra();
    return 0;
}
