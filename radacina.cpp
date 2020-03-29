/**
  *  Worg
  */
#include <vector>
#include <iomanip>
#include <fstream>

std::ifstream fin("radacina.in"); std::ofstream fout("radacina.out");

const int MIN_VAL = -20;
const int MAX_VAL = 20;
const double EPS = 1e-6;

bool check(std::vector<double>& pol, double x) {
    double result = 0, power = 1;

    for (double& coef : pol) {
        result += power * coef;
        power *= x;
    }

    return result < 0;
}

int main(int argc, char const *argv[]) {
    int n; fin >> n;
    std::vector<double> pol(n + 1);
    for (double& coef : pol) {
        fin >> coef;
    }


    double left = MIN_VAL, right = MAX_VAL;
    while (right - left > EPS) {
        double mid = (left + right) * 0.5;

        bool a = check(pol, left), b = check(pol, mid);

        if ((a ^ b) == 1) {
            right = mid;
        } else {
            left = mid;
        }
    }

    fout << right << '\n';
    return 0;
}
