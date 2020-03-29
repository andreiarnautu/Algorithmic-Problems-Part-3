/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>

std::ifstream fin("pscpld.in"); std::ofstream fout ("pscpld.out");

std::string get_transformed(std::string& initial) {
    std::string transformed; transformed.resize(2 * initial.size() + 1);

    for (int i = 0; i < (int)initial.size(); i++) {
        transformed[i * 2 + 1] = initial[i];
    }

    for (int i = 0; i < 2 * (int)initial.size() + 1; i += 2) {
        transformed[i] = '$';
    }

    return transformed;
}


long long count_palindromic_substrings(std::string str) {
    long long answer = 0;
    int index = -1, center = -1, n = (int)str.size();

    std::vector<int> len(n, 0);
    for (int i = 0; i < n; i++) {
        if (i <= index) {
            len[i] = std::min(index - i + 1, len[center - (i - center)]);
        }

        while (i - len[i] >= 0 && i + len[i] < n && str[i + len[i]] == str[i - len[i]]) {
            len[i]++;
        }

        answer += len[i] / 2;

        if (i + len[i] - 1 > index) {
            index = i + len[i] - 1;
            center = i;
        }
    }

    return answer;
}


int main() {
    std::string initial; fin >> initial;

    std::string transformed = get_transformed(initial);

    fout << count_palindromic_substrings(transformed) << '\n';
    return 0;
}
