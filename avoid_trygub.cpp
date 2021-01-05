/**
  *  Worg
  */
#include <string>
#include <vector>
#include <iostream>

int main() {
    int tests; std::cin >> tests;

    const std::string special = "bugyrt";
    for (int test = 0; test < tests; test++) {
        int n; std::cin >> n;
        std::string word; std::cin >> word;
        std::vector<int> freq(26, 0);

        for (int i = 0; i < n; i++) {
            freq[word[i] - 'a']++;
        }
        for (int i = 0; i < (int)special.size(); i++) {
            while (freq[special[i] - 'a']) {
                std::cout << special[i];
                freq[special[i] - 'a']--;
            }
        }
        for (char c = 'a'; c <= 'z'; c++) {
            while (freq[c - 'a']) {
                std::cout << c;
                freq[c - 'a']--;
            }
        }
        std::cout << '\n';
    }
    return 0;
}
