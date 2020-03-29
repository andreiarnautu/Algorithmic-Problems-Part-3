/**
  *  Worg
  */
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::ifstream fin ("joben.in"); std::ofstream fout("joben.out");

const int TETA = 26;

int main() {
    int test_count; fin >> test_count;

    for (int t = 0; t < test_count; t++) {
        std::string s1, s2; fin >> s1 >> s2;

        std::vector<int> f1(TETA, 0), f2(TETA, 0);

        for (int i = 0; i < (int)s1.size(); i++) {
            f1[s1[i] - 'a']++;
            f2[s2[i] - 'a']++;
        }

        std::sort(f1.begin(), f1.end());
        std::sort(f2.begin(), f2.end());


        std::string answer = "DA\n";
        for (int i = 0; i < TETA; i++) {
            if (f1[i] != f2[i]) {
                answer = "NU\n";
            }
        }

        fout << answer;
    }


    return 0;
}
