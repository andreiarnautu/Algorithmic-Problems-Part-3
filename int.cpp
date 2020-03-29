/**
  *  Worg
  */
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("int.in"); std::ofstream fout ("int.out");

int n;
std::set<int> coords;
std::map<int, int> my_map;
std::vector<std::pair<int, int>> intervals;

int curr_id;

void process_data() {
    fin >> n; intervals.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> intervals[i].first >> intervals[i].second;
        coords.insert(intervals[i].first); coords.insert(intervals[i].second);
    }


    for (int x: coords) {
        my_map[x] = ++curr_id;
    }
}


int get_answer() {
    std::vector<int> dp(curr_id + 1, 0);

    std::vector<std::vector<int>> add(curr_id + 1);

    for (std::pair<int, int> interval : intervals) {
        add[my_map[interval.second]].push_back(my_map[interval.first]);
    }

    for (int i = 1; i <= curr_id; i++) {
        dp[i] = std::max(dp[i], dp[i - 1]);

        for (int left_margin : add[i]) {
            dp[i] = std::max(dp[i], 1 + dp[left_margin]);
        }
    }

    return dp.back();
}


int main(int argc, char const *argv[]) {
    process_data();

    fout << get_answer() << '\n';

    return 0;
}
