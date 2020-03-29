/**
  *  Worg
  */
#include <vector>
#include <iostream>

bool check(std::vector<int>& arr, int paid, int needed) {
    int video_count = 0;

    for (int& num : arr) {
        if (video_count < num) {
            if (paid > 0) {
                video_count += 1;
                paid -= 1;
            }
        } else {
            video_count += 1;
        }
    }

    return video_count >= needed;
}

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<int> arr(n);

    for (int& elem : arr) {
        std::cin >> elem;
    }

   int left = 0, right = n, answer = n;

   while (left <= right) {
        int mid = (left + right) / 2;

        if (check(arr, mid, m)) {
            answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
   }
   std::cout << answer << '\n';

   return 0;
}
