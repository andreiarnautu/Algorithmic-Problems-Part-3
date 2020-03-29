/**
  *  Worg
  */
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("arbsat2.in"); std::ofstream fout("arbsat2.out");

void divide(int left, int right, std::vector<std::pair<int, int>>& v, std::set<std::pair<int, int>>& answer) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    divide(left, mid, v, answer);
    divide(mid + 1, right, v, answer);

    int axis = v[mid].first;
    for (int i = left; i <= right; i++) {
        if (v[i].first != axis) {
            answer.emplace(axis, v[i].second);
        }
    }
}

int main() {
    int n, m; fin >> n >> m;
    std::vector<std::pair<int, int>> v(n);
    std::set<std::pair<int, int>> answer;
    for (auto& p: v) {
        fin >> p.first >> p.second;
    }

    std::sort(v.begin(), v.end());
    divide(0, n - 1, v, answer);

    fout << answer.size() << "\n";
    for (auto& p: answer ) {
        fout << p.first << " " << p.second << "\n";
    }
    return 0;
}
