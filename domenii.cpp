/**
  *  Worg
  */
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <algorithm>

std::ifstream fin("domenii.in"); std::ofstream fout("domenii.out");

const int SIGMA = 26;

int main() {
    int n;
    std::string text;
    fin >> n >> text;

    std::vector<int> letter_freq(SIGMA, 0);

    int letter_count = 0;
    long long answer = 0, combination_count = 0;
    for (int i = (int)text.size() - 1; i >= 0; i--) {
        if (text[i] == '.') {
            answer += combination_count;
        } else {
            letter_count += 1;
            letter_freq[text[i] - 'a'] += 1;
            combination_count += letter_count - letter_freq[text[i] - 'a'];
        }
    }
    fout << answer << '\n';
    return 0;
}
