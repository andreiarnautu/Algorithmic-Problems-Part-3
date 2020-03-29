/**
 *  Worg
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

const int MAX_N = 300 + 1;
int f[4];
double steps[MAX_N][MAX_N][MAX_N], p[MAX_N][MAX_N][MAX_N];
//  p[{state}] = the probability of making it to this state
//  steps[{state}] = expected number of steps to get to this state

int main() {
	//  dp[i][j][k] = expected number of operations to remain with i 1-pieces, j 2-pieces and k 3-pieces
	//  Cand avem n farfurii, din care k nu sunt goale, care e expected-ul de pasi pana cand vom nimeri o farfurie care nu e goala?
	//  p_waste * (1 + S) = S <=> p_waste + S * (p_waste - 1) = 0 <=> p_waste = S * (1 - p_waste) <=> S = p_waste / (1 - p_waste)

	int n; std::cin >> n;
	for (int i = 0; i < n; i++) {
		int x; std::cin >> x;
		f[x] += 1;
	}

	p[f[1]][f[2]][f[3]] = 1;
	for (int c = n; c >= 0; c--) {
		for (int b = n; b >= 0; b--) {
			for (int a = n; a >= 0; a--) {
				if (a + b + c == 0 || a + b + c > n) continue;

				double p_waste = (double)(n - (a + b + c)) / n;
				double step_waste = 1 + p_waste / (1 - p_waste);
				steps[a][b][c] += step_waste * p[a][b][c];

				//  remove 1
				if (a > 0) {
					double p_here = (double) a / (a + b + c);
					p[a - 1][b][c] += p[a][b][c] * p_here;
					steps[a - 1][b][c] += steps[a][b][c] * p_here;
				}

				// remove 2
				if (b > 0) {
					double p_here = (double) b / (a + b + c);
					p[a + 1][b - 1][c] += p[a][b][c] * p_here;
					steps[a + 1][b - 1][c] += steps[a][b][c] * p_here;
				}

				//  remove 3
				if (c > 0) {
					double p_here = (double) c / (a + b + c);
					p[a][b + 1][c - 1] += p[a][b][c] * p_here;
					steps[a][b + 1][c - 1] += steps[a][b][c] * p_here;
				}
			}
		}
	}

	std::cout << std::fixed << std::setprecision(10) << steps[0][0][0] << "\n";
	return 0;
}
