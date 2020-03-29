/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
	//  Toate starile care au valori mai mici decat a[1] sunt pierzatoare.
	//  Daca prin recurenta ajungem la macar o stare care este pierzatoare, atunci starea curenta este castigatoare.
	//  Daca nu ajungem la nicio astfel de stare, atunci starea curenta este pierzatoare.
	int n, k; std::cin >> n >> k;
	std::vector<int> a(n);
	for (auto& x: a) {
		std::cin >> x;
	}


	std::vector<bool> winnable(k + 1, false);
	for (int i = 0; i <= k; i++) {
		for (auto& x: a) {
			if (i - x >= 0 && !winnable[i - x]) {
				winnable[i] = true;
			}
		}
	}

	if (winnable[k]) {
		std::cout << "First\n";
	} else {
		std::cout << "Second\n";
	}
	return 0;
}
