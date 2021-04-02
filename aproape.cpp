/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

const char FILE_IN[] = "aproape.in";
const char FILE_OUT[] = "aproape.out";

int task_one(int n) {
    int digits = 0;
    do {
        digits++;
        n /= 10;
    } while (n > 0);

    return digits;
}

std::vector<int> get_digits(int x) {
    std::vector<int> digits;

    do {
        digits.push_back(x % 10);
        x /= 10;
    } while (x);

    std::reverse(digits.begin(), digits.end());
    return digits;
}

void generate(std::set<int> &close_numbers, std::vector<int> &digits, int idx) {
    if (idx >= (int)digits.size()) {
        return;
    }

    //  add one to the current digit
    if (digits[idx] + 1 <= 9) {
        int new_number = 0;
        for (int i = 0; i < (int)digits.size(); i++) {
            if (i == idx) {
                new_number = new_number * 10 + (digits[i] + 1);
            } else {
                new_number = new_number * 10 + digits[i];
            }
        }

        close_numbers.insert(new_number);
    }

    //  subtract one from the current digit
    if (((idx > 0 || digits.size() == 1) && digits[idx] - 1 == 0) || digits[idx] - 1 > 0) {
        int new_number = 0;
        for (int i = 0; i < (int)digits.size(); i++) {
            if (i == idx) {
                new_number = new_number * 10 + (digits[i] - 1);
            } else {
                new_number = new_number * 10 + digits[i];
            }
        }

        close_numbers.insert(new_number);
    }

    //  don't change the current number and move on to the next digit
    generate(close_numbers, digits, idx + 1);
}

int task_two(int n) {
    std::vector<int> digits = get_digits(n);
    std::set<int> close_numbers;

    generate(close_numbers, digits, 0);

    return (int)close_numbers.size();
}

int task_three(int n) {
    std::vector<int> initial_digits = get_digits(n);
    std::set<int> close_numbers_0;

    generate(close_numbers_0, initial_digits, 0);

    std::set<int> close_numbers_1;
    for (int close_number : close_numbers_0) {
        std::vector<int> new_digits = get_digits(close_number);
        generate(close_numbers_1, new_digits, 0);
    }

    return (int)close_numbers_1.size();
}

int main(int argc, char **argv) {
    FILE* in_file = fopen(FILE_IN, "r");
    int task, n;
    fscanf(in_file, "%d%d", &task, &n);
    fclose(in_file);

    int answer;
    if (task == 1) {
        answer = task_one(n);
    } else if (task == 2) {
        answer = task_two(n);
    } else {
        answer = task_three(n);
    }

    FILE* out_file = fopen(FILE_OUT, "w");
    fprintf(out_file, "%d\n", answer);
    fclose(out_file);
    return 0;
}
