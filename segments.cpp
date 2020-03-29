/**
  *  Worg
  */
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    std::vector<std::pair<int, int>> segments(n);
    for (auto& segment: segments) {
        std::cin >> segment.first >> segment.second;

        if (segment.first > segment.second) {
            std::swap(segment.first, segment.second);
        }
    }
    std::sort(segments.begin(), segments.end());

    std::set<int> end_points;
    std::vector<int> answer;
    for (int i = 0; i < n; i++) {
        end_points.insert(segments[i].second);

        if (i + 1 < n && *end_points.begin() < segments[i + 1].first) {
            answer.push_back(*end_points.begin());
            end_points.clear();
        }
    }

    if (!end_points.empty()) {
        answer.push_back(*end_points.begin());
    }

    std::cout << answer.size() << '\n';
    for (auto& x: answer) {
        std::cout << x << " ";
    }
    std::cout << '\n';

    return 0;
}
