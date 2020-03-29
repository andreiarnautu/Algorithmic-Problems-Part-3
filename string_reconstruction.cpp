/**
  *  Worg
  */
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

const int MAX_LEN = 2e6 + 1;

//std::map<int, std::vector<std::pair<int, int>>> events;

int main() {
    int n; std::cin >> n;
    int size = 0;

    std::vector<std::vector<std::pair<int, int>>> events(MAX_LEN);

    std::vector<std::string> words(n);
    for (int i = 0; i < n; i++) {
        std::cin >> words[i];
        int k; std::cin >> k;
        for (int j = 0; j < k; j++) {
            int start; std::cin >> start;
            events[start].emplace_back(start + words[i].size() - 1, i);
            size = std::max(size, start + (int)words[i].size() - 1);
        }
    }
    std::string answer;

    int range = 0, start = 0, word_id = 0;
    for (int i = 1; i <= size; i++) {
        for (auto& p: events[i]) {
            if (range < p.first) {
                range = p.first;
                word_id = p.second;
                start = i;
            }
        }

        if (i <= range) {
            answer += words[word_id][i - start];
        } else {
            answer += 'a';
        }
    }
    std::cout << answer << '\n';
    return 0;
}
