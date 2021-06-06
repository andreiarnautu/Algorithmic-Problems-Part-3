/**
 *  Worg
 */
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

const int INF = 1e9;
const char FILE_IN[] = "labirint2.in";
const char FILE_OUT[] = "labirint2.out";

class Solver {
public:
    Solver() {
        fin = std::ifstream(FILE_IN);
        fout = std::ofstream(FILE_OUT);
    }

    void read_input() {
        fin >> n >> m;
        mat.resize(n);
        for (int i = 0; i < n; i++) {
            fin >> mat[i];
        }
        fin.close();
    }

    void compute_distances() {
        dmin_begin = dmin_end = std::vector<std::vector<int>>(n, std::vector<int>(m, INF));
        bfs(0, 0, dmin_begin);
        bfs(n - 1, m - 1, dmin_end);
    }

    void compute_solution() {
        int d0 = dmin_end[0][0];
        solution.resize(n);

        for (int i = 0; i < n; i++) {
            solution[i].resize(m);

            for (int j = 0; j < m; j++) {
                if (mat[i][j] == '0') {
                    solution[i][j] = '0';
                } else {
                    int best_begin = INF;
                    int best_end = INF;

                    for (int k = 0; k < 4; k++) {
                        int x = i + dx[k];
                        int y = j + dy[k];

                        if (is_valid(x, y)) {
                            best_begin = std::min(best_begin, dmin_begin[x][y]);
                            best_end = std::min(best_end, dmin_end[x][y]);
                        }
                    }

                    solution[i][j] = (best_begin + best_end + 2 < d0) ? '1' : '0';
                }
            }
        }
    }

    void print_solution() {
        for (int i = 0; i < n; i++) {
            fout << solution[i] << '\n';
        }
        fout.close();
    }


private:
    std::ifstream fin;
    std::ofstream fout;
    int n, m;
    std::vector<std::string> mat;
    std::vector<std::vector<int>> dmin_begin;
    std::vector<std::vector<int>> dmin_end;
    std::vector<std::string> solution;
    const std::vector<int> dx = {-1, 1, 0, 0};
    const std::vector<int> dy = { 0, 0,-1, 1};

    bool is_valid(int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    }

    void bfs(int start_x, int start_y, std::vector<std::vector<int>>& dmin) {
        std::queue<std::pair<int, int>> queue;
        queue.emplace(start_x, start_y);
        dmin[start_x][start_y] = 0;

        while (!queue.empty()) {
            int x = queue.front().first;
            int y = queue.front().second;
            queue.pop();

            for (int i = 0; i < 4; i++) {
                int new_x = x + dx[i];
                int new_y = y + dy[i];

                if (is_valid(new_x, new_y) && mat[new_x][new_y] == '0' && dmin[new_x][new_y] == INF) {
                    dmin[new_x][new_y] = dmin[x][y] + 1;
                    queue.emplace(new_x, new_y);
                }
            }
        }
    }


};

int main() {
    Solver solver;
    solver.read_input();
    solver.compute_distances();
    solver.compute_solution();
    solver.print_solution();
    return 0;
}
