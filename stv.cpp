/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("stv.in"); std::ofstream fout("stv.out");

int n, m;
std::vector<std::vector<int> > votes;

void read_data() {
    fin >> n >> m;
    votes.resize(n);
    for (int i = 0; i < n; i++) {
        int count; fin >> count;
        for (int j = 0; j < count; j++) {
            int x; fin >> x;
            x--;  //  for 0-indexing
            votes[i].push_back(x);
        }
        std::reverse(votes[i].begin(), votes[i].end());
    }
}

void solve() {
    std::vector<bool> seen(m, false);
    std::vector<int> answer;

    for (int i = 0; i < m; i++) {
        std::vector<int> count(m, 0);

        for (int j = 0; j < n; j++) {
            while (!votes[j].empty() && seen[votes[j].back()]) {
                votes[j].pop_back();
            }

            if (!votes[j].empty()) {
                count[votes[j].back()]++;
            }
        }

        int min_votes = n + 1, candidate = -1;
        for (int j = 0; j < m; j++) {
            if (!seen[j] && count[j] <= min_votes) {
                min_votes = count[j];
                candidate = j;
            }
        }

        answer.push_back(candidate + 1);
        seen[candidate] = true;
    }

    std::reverse(answer.begin(), answer.end());
    for (auto& x : answer) {
        fout << x << " ";
    }
}

int main() {
    read_data();
    solve();
    return 0;
}
