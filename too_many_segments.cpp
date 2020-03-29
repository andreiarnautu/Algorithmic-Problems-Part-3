/**
  *  Worg
  */
#include <set>
#include <vector>
#include <cassert>
#include <iostream>

const int MAX_N = 2e5 + 2;

int main(int argc, char const *argv[]) {
    int n, k; std::cin >> n >> k;

    std::vector<std::pair<int, int>> segments(n + 1);
    std::vector<int> mars(MAX_N, 0);
    std::vector<std::vector<int>> events(MAX_N);

    for (int i = 1; i <= n; i++) {
        std::cin >> segments[i].first >> segments[i].second;
        mars[segments[i].first] += 1;
        mars[segments[i].second + 1] -= 1;

        events[segments[i].first].push_back(i);
        events[segments[i].second + 1].push_back(-i);
    }

    for (int i = 1; i < MAX_N; i++) {
        mars[i] += mars[i - 1];
    }


    //  Compute answer
    std::vector<bool> is_deleted(n + 1, false);
    std::vector<int> sub(MAX_N, 0);
    std::set<std::pair<int, int>> active_segments;

    int count_deleted = 0;

    for (int i = 0, curr_sub = 0; i < MAX_N; i++) {
        curr_sub += sub[i];

        for (auto& event_id : events[i]) {
            if (event_id > 0) {
                active_segments.emplace(segments[event_id].second, event_id);
            } else {
                auto it = active_segments.find(std::make_pair(segments[-event_id].second, -event_id));

                if (it != active_segments.end()) {
                    active_segments.erase(it);
                }
            }
        }

        while (mars[i] - curr_sub > k) {
            int event_id = active_segments.rbegin()->second;
            active_segments.erase(std::prev(active_segments.end()));
            curr_sub += 1;
            --sub[segments[event_id].second + 1];
            is_deleted[event_id] = true;
            count_deleted += 1;
        }
    }

    std::cout << count_deleted << '\n';
    for (int i = 1; i <= n; i++) {
        if (is_deleted[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << '\n';
    return 0;
}
