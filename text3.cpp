/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("text3.in"); std::ofstream fout("text3.out");

const int TETA = 26;

int main() {
	int word_count = 0;
	std::string word;

	std::vector<std::string> words;
	std::vector<int> last(TETA, -1), best(TETA, 0), prev;

	int last_word = -1, max_length = -1;

	while (fin >> word) {
    	words.push_back(word);
		prev.push_back(last[word[0] - 'a']);

		int score = best[word[0] - 'a'] + 1;
		if (score > best[word.back() - 'a']) {
			best[word.back() - 'a'] = score;
			last[word.back() - 'a'] = word_count;
		}

		if (score > max_length) {
			max_length = score;
			last_word = word_count;
		}
		word_count += 1;
	}

	fout << word_count << "\n" << word_count - max_length << "\n";

	std::vector<std::string> solution;
	while (last_word != -1) {
		solution.push_back(words[last_word]);
		last_word = prev[last_word];
	}

	std::reverse(solution.begin(), solution.end());
	for (auto& word : solution) {
		fout << word << "\n";
	}
	return 0;
}

