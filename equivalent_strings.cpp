/**
  *  Worg
  */
#include <string>
#include <iostream>

std::string get_minimal_equivalent(std::string s) {
    if (s.size() % 2 == 1) {
        return s;
    }

    std::string e1 = get_minimal_equivalent(s.substr(0, s.size() / 2));
    std::string e2 = get_minimal_equivalent(s.substr(s.size() / 2, s.size()));

    if (e1 < e2) {
        return e1 + e2;
    }
    return e2 + e1;
}

int main() {
    std::string s1, s2; std::cin >> s1 >> s2;

    std::string e1 = get_minimal_equivalent(s1);
    std::string e2 = get_minimal_equivalent(s2);

    if (e1 == e2) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
