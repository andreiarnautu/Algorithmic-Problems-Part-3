/**
  *  Worg
  */
#include <iostream>
#include <algorithm>

int main() {
	int a1, a2, k1, k2, n;
	std::cin >> a1 >> a2 >> k1 >> k2 >> n;
	
	std::cout << std::max(0, n - a1 * (k1 - 1) - a2 * (k2 - 1)) << " ";
	
	if (k1 > k2) {
		std::swap(k1, k2);
		std::swap(a1, a2);
	}
	
	if (n <= a1 * k1) {
		std::cout << n / k1 << '\n';
	} else {
		n -= a1 * k1;
		std::cout << a1 + n / k2 << '\n';
	}
	
	return 0;
}
