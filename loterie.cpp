/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("loterie.in"); std::ofstream fout("loterie.out");

const int MAX_A = 100 + 1;
const int MAX_B = 50000 + 1;

int phi[MAX_B];
long long phi_sum[MAX_B];
std::vector<int> fact[MAX_A];

//  Computes phi and a partial sums array over it.
void precompute_phi() {
    for (int i = 2; i < MAX_B; i++) {
        phi[i] = i;
    }

    for (int i = 2; i < MAX_B; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MAX_B; j += i) {
                phi[j] = (phi[j] / i) * (i - 1);
            }
        }

        phi_sum[i] = phi_sum[i - 1] + phi[i];
    }
}

//  Does prime factors decomposition for numbers < MAX_A
void precompute_factors() {
    for (int i = 2; i < MAX_A; i++) {
        if (fact[i].size() == 0) {
            fact[i].push_back(i);

            for (int j = 2 * i; j < MAX_A; j += i) {
                fact[j].push_back(i);
            }
        }
    }
}

//  Returns the number of values in range [a, b] that are multiples of value
int count_interval_multiples(int a, int b, int value) {
    if (a > b) return 0;

    int answer = b / value - a / value + 1;
    return answer - (a % value != 0 ? 1 : 0);
}

//  Returns the number of values in range [a, b] which are coprimes with x
int pinex(int a, int b, int x) {
    int answer = b - a + 1;
    for (int mask = 1; mask < (1 << fact[x].size()); mask++) {
        int product = 1, active_bits = 0;

        for (int i = 0; i < (int)fact[x].size(); i++) {
            if (mask & (1 << i)) {
                product *= fact[x][i];
                active_bits++;
            }
        }

        if (active_bits % 2 == 1) {
            answer -= count_interval_multiples(a, b, product);
        } else {
            answer += count_interval_multiples(a, b, product);
        }
    }
    return answer;
}

void solve_queries() {
    int query_count;
    fin >> query_count;

    for (int i = 0; i < query_count; i++) {
        int a, b;
        fin >> a >> b;

        long long answer = phi_sum[b] - phi_sum[a - 1];
        for (int small_number = 1; small_number < a; small_number++) {
            answer -= pinex(a, b, small_number);
        }
        fout << answer << '\n';
    }
}

int main() {
    precompute_phi();
    precompute_factors();
    solve_queries();
    return 0;
}
