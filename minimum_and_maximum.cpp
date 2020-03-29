/**
  *  Worg
  */
#include <vector>
#include <iostream>

char ask(int i, int j) {
    char verdict;
    std::cout << "? " << i << " " << j << '\n';
    std::cout.flush();
    std::cin >> verdict;
    return verdict;
}

std::pair<int, int> SolveEven(int n) {
    std::vector<int> min_array, max_array;

    for (int i = 1; i <=  n; i += 2) {
        char verdict = ask(i, i + 1);

        if (verdict == '<') {
            min_array.push_back(i); max_array.push_back(i + 1);
        } else {
            min_array.push_back(i + 1); max_array.push_back(i);
        }
    }

    int min_id = min_array.front();
    for (int i = 1; i < (int)min_array.size(); i++) {
        char verdict = ask(min_id, min_array[i]);
        if (verdict != '<') {
            min_id = min_array[i];
        }
    }

    int max_id = max_array.front();
    for (int i = 1; i < (int)max_array.size(); i++) {
        char verdict = ask(max_id, max_array[i]);
        if (verdict != '>') {
            max_id = max_array[i];
        }
    }

    return std::make_pair(min_id, max_id);
}


std::pair<int, int> SolveOdd(int n) {
    if (n == 1) {
        return std::make_pair(1, 1);
    }

    std::pair<int, int> partial_answer = SolveEven(n - 1);

    int min_id = partial_answer.first, max_id = partial_answer.second;
    char verdict;

    verdict = ask(n, min_id);
    if (verdict == '<') {
        min_id = n;
    }

    verdict = ask(n, max_id);
    if (verdict == '>') {
        max_id = n;
    }

    return std::make_pair(min_id, max_id);
}

int main(int argc, char const *argv[]) {
    int test_count; std::cin >> test_count;

    for (int i = 0; i < test_count; i++) {
        int n; std::cin >> n;

        std::pair<int, int> answer;
        if (n % 2 == 0) {
            answer = SolveEven(n);
        } else {
            answer = SolveOdd(n);
        }

        std::cout << "! " << answer.first << " " << answer.second << '\n';
        std::cout.flush();
    }

    return 0;
}
