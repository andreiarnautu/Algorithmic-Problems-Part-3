/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>

int main() {
    int n; std::cin >> n;
    std::string s, t; std::cin >> s >> t;

    std::vector<int> id1, id2;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a' && t[i] == 'b') {
            id1.push_back(i);
        } else if (s[i] == 'b' && t[i] == 'a') {
            id2.push_back(i);
        }
    }


    if ((id1.size() + id2.size()) % 2 == 1) {
        std::cout << "-1\n";
    } else {
        std::vector<std::pair<int, int>> moves;

        while (id1.size() >= 2) {
            int x = id1.back(); id1.pop_back();
            int y = id1.back(); id1.pop_back();
            moves.emplace_back(x, y);
        }

        while (id2.size() >= 2) {
            int x = id2.back(); id2.pop_back();
            int y = id2.back(); id2.pop_back();
            moves.emplace_back(x, y);
        }

        if(!id1.empty()) {
            moves.emplace_back(id1.back(), id1.back());
            moves.emplace_back(id1.back(), id2.back());
        }

        std::cout << moves.size() << '\n';
        for (auto pair : moves) {
            std::cout << pair.first + 1 << " " << pair.second + 1 << '\n';
        }
    }

    return 0;
}
