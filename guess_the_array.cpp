/**
  *  Worg
  */
#include <vector>
#include <iostream>


int main(int argc, char const *argv[]) {
    int n; std::cin >> n;

    std::vector<int> answer(n);

    int s1; std::cout << "? 1 2\n"; std::cout.flush(); std::cin >> s1;
    int s2; std::cout << "? 1 3\n"; std::cout.flush(); std::cin >> s2;
    int s3; std::cout << "? 2 3\n"; std::cout.flush(); std::cin >> s3;
    int s = (s1 + s2 + s3) / 2;

    answer[0] = s - s3; answer[1] = s - s2; answer[2] = s - s1;

    for (int i = 3; i < n; i++) {
        int s; std::cout << "? 1 " << i + 1 << '\n'; std::cout.flush(); std::cin >> s;

        answer[i] = s - answer[0];
    }

    std::cout << "! ";
    for (int& num : answer) {
        std::cout << num << " ";
    }
    std::cout << '\n';
    std::cout.flush();

    return 0;
}
