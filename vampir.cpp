/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("vampir.in"); std::ofstream fout("vampir.out");

const int MOD = 1e9 + 7;

long long raise(long long base, long long exp) {
    long long answer = 1, aux = base;
    for (long long i = 1; i <= exp; i <<= 1) {
        if (i & exp) {
            answer = answer * aux % MOD;
        }
        aux = aux * aux % MOD;
    }
    return answer;
}


int main(int argc, char **argv) {
    int task, len; fin >> task >> len;
    len /= 2;

    if (len % 2 == 1) {
        fout << "-1\n"; return 0;
    }

    if (task == 1) {
        std::vector<int> divs;
        for (int i = 2; i <= len; i += 2) {
            if (len % i == 0) {
                divs.push_back(i);
            }
        }

        fout << divs.size() << "\n";
        for (auto& div : divs) {
            fout << div << " ";
        }
        fout << "\n";
    } else {
        long long fact = 1, answer;
        for (int i = 1; i <= len / 2 - 1; i++) {
            fact = fact * i % MOD;
        }
        answer = fact * fact % MOD;

        fact = 1;
        for (int i = 1; i <= len - 1; i++) {
            fact = fact * i % MOD;
        }

        answer = answer * raise(fact, MOD - 2) % MOD;
        fout << answer << "\n";
    }


    return 0;
}
