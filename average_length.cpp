/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

int n;
std::vector<std::pair<double, double>> pts;

double dist(std::pair<double, double> a, std::pair<double, double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    std::cin >> n;
    pts.resize(n);
    for (auto& p: pts) {
        std::cin >> p.first >> p.second;
    }

    std::vector<int> perm;
    for (int i = 1; i <= n; i++) {
        perm.push_back(i);
    }

    double total_dist = 0, ways = 0;
    do {
        ways += 1;
        for (int i = 1; i < (int)perm.size(); i++) {
            total_dist += dist(pts[perm[i] - 1], pts[perm[i - 1] - 1]);
        }
    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << std::fixed << std::setprecision(9) << total_dist / ways << "\n";
    return 0;
}
