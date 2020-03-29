/**
  *  Worg
  */
#include <iostream>

int main() {
    int a1, a2, a3, a4; std::cin >> a1 >> a2 >> a3 >> a4;
    if (a1 + a2 == a3 + a4 || a1 + a3 == a2 + a4 || a1 + a4 == a2 + a3) {
        std::cout << "YES\n";
    } else if (a1 == a2 + a3 + a4 || a2 == a1 + a3 + a4 || a3 == a1 + a2 + a4 || a4 == a1 + a2 + a3) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
