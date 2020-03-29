/**
  *  Worg
  */
#include <deque>
#include <string>
#include <iostream>

int n;
std::string str;

bool get_verdict(std::deque<int>& packmen, std::deque<int>& food, const int& time) {
    if (food.empty()) {
        return true;
    }
    if (packmen.empty()) {
        return false;
    }

    int x1, x2, y;
    if (packmen.size() == 1) {
        x1 = x2 = 0;

        if (food.front() < packmen[0]) {
            x1 = packmen[0] - food.front();
        }
        if (food.back() > packmen[0]) {
            x2 = food.back() - packmen[0];
        }

        return time >= (2 * std::min(x1, x2) + std::max(x1, x2));
    }

    //  Sa vedem cat acopera packmanul din stanga
    x1 = x2 = 0;

    if (food.front() < packmen[0]) {
        x1 = packmen[0] - food.front();
    }
    y = time - 2 * x1;
    if (time - x1 >= 0) {
        y = std::max(y, (time - x1) / 2);
    }

    if (y < 0) {
        return false;
    } else {
        while(!food.empty() && food.front() <= packmen.front() + y) {
            food.pop_front();
        }
    }

    if (food.empty()) return true;

    //  Acum packmanul din dreapta
    x1 = x2 = 0;

    if (food.back() > packmen.back()) {
        x1 = food.back() - packmen.back();
    }
    y = time - 2 * x1;

    if (time - x1 >= 0) {
        y = std::max(y, (time - x1) / 2);
    }

    if (y < 0) {
        return false;
    } else {
        while (!food.empty() && food.back() >= packmen.back() - y) {
            food.pop_back();
        }
    }

    packmen.pop_front(); packmen.pop_back();
    return get_verdict(packmen, food, time);
}

bool check(const int time) {
    std::deque<int> packmen;
    std::deque<int> food;

    for (int i = 0; i < n; i++) {
        if (str[i] == '*') {
            food.push_back(i);
        } else if (str[i] == 'P') {
            packmen.push_back(i);
        }
    }

    return get_verdict(packmen, food, time);
}

int main() {
    std::cin >> n;
    std::cin >> str;

    int left = 1, right = 4 * n, answer = 4 * n;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(mid)) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    std::cout << answer << '\n';
    return 0;
}
