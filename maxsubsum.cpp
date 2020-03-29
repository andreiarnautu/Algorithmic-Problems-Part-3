/**
  *  Worg
  */
#include <vector>
//#include <iostream>

#include <fstream>
std::ifstream fin("maxsubsum.in"); std::ofstream fout("maxsubsum.out");

const int inf = 1e9;

int main(int argc, char const *argv[]) {
    int n, m; fin >> n >> m;

    std::vector<int> a(n), b(m);
    for (auto& num : a) {
        fin >> num;
    }
    for (auto& num : b) {
        fin >> num;
    }

    std::vector<long long> dpa(n + 1), dpb(m + 1);
    for (int i = 0; i <= n; i++) {
        dpa[i] = - 1LL * inf * i;
    }
    for (int i = 0; i <= m; i++) {
        dpb[i] = -1LL * inf * i;
    }

    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            dpa[j - i + 1] = std::max(dpa[j - i + 1], sum);
        }
    }

    for (int i = 0; i < m; i++) {
        long long sum = 0;
        for (int j = i; j < m; j++) {
            sum += b[j];
            dpb[j - i + 1] = std::max(dpb[j - i + 1], sum);
        }
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            ans = std::max(ans, 1LL * i * dpb[j] + 1LL * j * dpa[i]);
        }
    }
    fout << ans << '\n';
    return 0;
}
