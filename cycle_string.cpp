/**
  *  Worg
  */
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const int TETA = 26;

void print_after_frequency(std::vector<int>& freq) {
	std::cout << "YES\n";
	for (int i = 0; i < TETA; i++) {
		char ch = 'a' + i;

		for (int j = 0; j < freq[i]; j++) {
			std::cout << ch;
		}
	}
	std::cout << '\n';
}

void print_impossible() {
	std::cout << "NO\n";
	exit(0);
}

std::vector<std::pair<int,int>> get_chars(std::vector<int>& freq) {
	std::vector<std::pair<int, int>> chars;
	for (int i = 0; i < TETA; i++) {
		if (freq[i] != 0) {
			chars.emplace_back(freq[i], i);
		}
	}
	std::sort(chars.begin(), chars.end());
	return chars;
}

void function() {

}

void case_six(std::vector<int>& freq, int max_freq) {
	if (max_freq > 4) {
		print_impossible();
	}

	//  Ok, deci max_freq = 4. Atunci trebuie ca cele doua caractere diferite de cel principal sa fie diferite intre ele
	std::vector<std::pair<int,int>> chars = get_chars(freq);

	std::sort(chars.begin(), chars.end());
	if (chars.size() == 2) {
		print_impossible();
	}

	char ch1 = 'a' + chars[2].second;
	char ch2 = 'a' + chars[1].second;
	char ch3 = 'a' + chars[0].second;

	std::cout << "YES\n";
	std::cout << ch1 << ch1 << ch1 << ch2 << ch1 << ch3 << '\n';
	exit(0);
}

void print_big_case(std::vector<std::pair<int, int>> chars, int n) {
	std::string result; result.resize(n);

	for (int i = 0; i < n / 2; i++) {
		result[i] = ('a' + chars.back().second);
		chars.back().first -= 1;
	}

	int begin = n / 2, end = n - 1;

	result[end] = ('a' + chars[0].second);
	chars[0].first -= 1;
	end -= 1;

	if (chars.size() == 2) {
		result[begin] = result[begin + 1] = ('a' + chars[0].second);
		chars[0].first -= 2;
		begin += 2;
	} else {
		result[begin] = ('a' + chars[1].second);
		chars[1].first -= 1;
		begin += 1;
	}

	for (int i = begin, id = 0; i <= end; i++) {
		while (chars[id].first == 0) {
			id += 1;
		}

		result[i] = ('a' + chars[id].second);
		chars[id].first -= 1;
	}
	std::cout << "YES\n" << result << '\n';
	exit(0);
}

int main() {
	std::string s; std::cin >> s;
	int n = (int)s.size();

	std::vector<int> freq(TETA, 0);
	for (int i = 0; i < n; i++) {
		freq[s[i] - 'a'] += 1;
	}

	int max_freq = 0;
	for (int i = 0; i < TETA; i++) {
		max_freq = std::max(max_freq, freq[i]);
	}

	if (max_freq <= n / 2) {
		print_after_frequency(freq); return 0;
	}

	//  Avem clar un caracter care apare de mai mult de jumate din ori. Tratam diversele cazuri.
	if (max_freq == n || n == 4) {
		print_impossible();
	}

	if (n == 6) {
		case_six(freq, max_freq);
	} else {
		std::vector<std::pair<int, int>> chars = get_chars(freq);

		if (chars.size() == 2 && chars[0].first <= 2) {
			print_impossible();
		} else {
			print_big_case(chars, n);
		}
	}

	return 0;
}
