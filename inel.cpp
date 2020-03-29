/**
  *  Worg
  */
#include <vector>
#include <fstream>

std::ifstream fin("inel.in"); std::ofstream fout("inel.out");

std::vector<bool> compute_primes(int n) {
    std::vector<bool> prime(2 * n, true);

    for (int i = 2; i < 2 * n; i++) {
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                prime[i] = false;
            }
        }
    }

    return prime;
}

std::vector<std::vector<int>> compute_next(int n, std::vector<bool> &prime) {
    std::vector<std::vector<int>> next(n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j && prime[i + j]) {
                next[i].push_back(j);
            }
        }
    }

    return next;
}

void back(int step, int n, int& answer, std::vector<int>& nums, std::vector<bool>& prime, std::vector<bool>& used, std::vector<std::vector<int>>& next) {
    if (step == n) {
        answer += prime[nums[0] + nums[n - 1]];
        return;
    }

    for (int& x : next[nums[step - 1]]) {
        if (!used[x]) {
            nums[step] = x;
            used[x] = true;
            back(step + 1, n, answer, nums, prime, used, next);
            used[x] = false;
        }
    }
}

int main() {
    int n; fin >> n;
    std::vector<bool> prime = compute_primes(n), used(n + 1, false);
    std::vector<std::vector<int>> next = compute_next(n, prime);
    std::vector<int> nums(n);
    nums[0] = 1; used[1] = true;

    int answer = 0;
    back(1, n, answer, nums, prime, used, next);
    fout << answer << '\n';
    fin.close(); fout.close();
    return 0;
}