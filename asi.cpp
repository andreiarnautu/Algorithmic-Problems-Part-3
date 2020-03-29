/**
  *  Worg
  */
#include <vector>
#include <bitset>
#include <fstream>
#include <algorithm>

std::ifstream fin("asi.in"); std::ofstream fout("asi.out");

const int MAX_ROOT = 1e6 + 1;

std::vector<int> thresholds(40);
std::vector<int> primes;
std::vector<std::vector<long long>> powers(40, std::vector<long long>());
std::bitset<MAX_ROOT> marked;

void compute_primes() {
    for (int i = 3; i * i < MAX_ROOT; i += 2) {
        if (!marked[i]) {
            for (int j = i * i; j < MAX_ROOT; j += 2 * i) {
                marked[j] = true;
            }
        }
    }

    primes.push_back(2);
    for (int i = 3; i < MAX_ROOT; i += 2) {
        if (!marked[i]) {
            primes.push_back(i);
        }
    }
}


void compute_thresholds() {
    for (int power = 2; power < 40; power++) {
        int x = 0;

        for (int i = 0; i < (int)primes.size(); i++) {
            long long curr_value = 1, max_value = 1LL * MAX_ROOT * MAX_ROOT;
            for (int j = 1; j <= power; j++) {
                if (max_value / curr_value < primes[i]) {
                    curr_value = -1; break;
                }
                curr_value *= primes[i];
            }

            if (curr_value != -1) {
                x = i;
            } else {
                break;
            }
        }

        thresholds[power] = x;
    }
}

void compute_powers() {
    for (int i = 0; i < (int)primes.size(); i++) {
        long long value = primes[i];
        for (int power = 2; power < 40; power++) {
            if (i > thresholds[power]) break;
            value *= primes[i];
            powers[power].push_back(value);
        }
    }
}


void solve_test() {
    long long a, b; fin >> a >> b;

    int answer = 0;
    long long left, right, mid, min_value, max_value;

    for (int power = 2; power < 40; power++) {
        //  Binary search the smallest value
        left = 0, right = (int)powers[power].size() - 1, min_value = -1;
        while (left <= right) {
            mid = (left + right) / 2;

            if (powers[power][mid] >= a) {
                min_value = mid; right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (min_value == -1) continue;

        //  Biggest value
        left = min_value, right = (int)powers[power].size() - 1, max_value = -1;
        while (left <= right) {
            mid = (left + right) / 2;

            if (powers[power][mid] <= b) {
                max_value = mid; left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (max_value == -1) {
            continue;
        }
        answer += max_value - min_value + 1;
    }

    fout << answer << "\n";
}


int main(int argc, char **argv) {
    compute_primes();
    compute_thresholds();
    compute_powers();

    int query_count; fin >> query_count;
    for (int i = 0; i < query_count; i++) {
        solve_test();
    }

    return 0;
}
