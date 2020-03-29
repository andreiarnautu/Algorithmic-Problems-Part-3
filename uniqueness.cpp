/**
  *  Worg
  */
#include <map>
#include <vector>
#include <iostream>


int main(int argc, char const *argv[]) {
    int n; std::cin >> n;
    std::vector<int> vec(n);

    for(auto& elem : vec) {
        std::cin >> elem;
    }

    int ans = n - 1;
    std::map<int, int> frq;

    for (int i = 0; i < n; i++) {
        int bad = 0;
        for (int j = 0; j < n; j++) {
            frq[vec[j]]++;

            if (frq[vec[j]] == 2) {
                bad++;
            }
        }

        if(bad == 0) {
            ans = 0; break;
        }
        //std::cout << bad << '\n';

        for (int j = i; j < n; j++) {
            frq[vec[j]]--;
            if (frq[vec[j]] == 1) {
                bad--;

                if (bad == 0) {
                    ans = std::min(ans, j - i + 1); break;
                }
            }
        }

        for (int j = 0; j < n; j++) {
            frq[vec[j]] = 0;
        }
    }

    std::cout << ans << '\n';
    return 0;
}
