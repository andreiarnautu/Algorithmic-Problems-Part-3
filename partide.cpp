/**
  *  Worg
  */
#include <vector>
#include <cstdlib>
#include <fstream>
#include <algorithm>

std::ifstream fin("partide.in"); std::ofstream fout("partide.out");

int n, total_games;
std::vector<int> games;

int get_min(int banned_id) {
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (i != banned_id && games[i] && (answer == 0 || games[i] < games[answer])) {
            answer = i;
        }
    }
    return answer;
}


int get_max(int banned_id) {
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (i != banned_id && games[i] > games[answer]) {
            answer = i;
        }
    }
    return answer;
}

void check_endgame(int prev_winner) {
    for (int i = 1; i <= n; i++) {
        if (games[i] == total_games) {
            if (prev_winner) {
                fout << i << " " << prev_winner << '\n';
                games[i] -= 1;
                games[prev_winner] -= 1;
            }
            while (games[i]) {
                int other = get_min(i);
                fout << i << " " << other << '\n';
                games[i] -= 1;
                games[other] -= 1;
            }
            exit(0);
        }
    }
}


int main(int argc, char **argv) {
    fin >> n;

    games = std::vector<int>(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> games[i];
        total_games += games[i];
    }
    total_games >>= 1;
    fout << total_games << '\n';

    int prev_winner = 0;
    while (total_games) {
        check_endgame(prev_winner);

        if (!prev_winner) {
            prev_winner = get_max(0);
        }

        if (games[prev_winner] == 1) {
            //  time to lose
            int other = get_max(prev_winner);
            fout << other << " " << prev_winner << '\n';

            games[prev_winner] -= 1;
            games[other] -= 1;
            total_games -= 1;
            prev_winner = other;
        } else {
            int other = get_min(prev_winner);
            fout << prev_winner << " " << other << '\n';

            games[prev_winner] -= 1;
            games[other] -= 1;
            total_games -= 1;
        }
    }


    return 0;
}
