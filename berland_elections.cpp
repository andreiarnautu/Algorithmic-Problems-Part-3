/**
  *  Worg
  */
#include <vector>
#include <iostream>
#include <algorithm>
const int MAX_N = 100 + 1;

struct Candidate {
    int id, votes, last_vote;

    Candidate() {
        id = votes = last_vote = 0;
    }

    bool operator <(const Candidate &other) const {
        if (this->votes != other.votes) {
            return this->votes > other.votes;
        }
        return this->last_vote < other.last_vote;
    }
};

int n, k, m, a;
std::vector<Candidate> candidates;

void read_input() {
    std::cin >> n >> k >> m >> a;

    candidates.resize(n);
    for (int i = 0; i < n; i++) {
        candidates[i].id = i;
    }

    for (int i = 0; i < a; i++) {
        int vote; std::cin >> vote;
        candidates[vote - 1].votes += 1;
        candidates[vote - 1].last_vote = i + 1;
    }
}

int get_verdict(int id) {
    for (int i = 0; i < n; i++) {
        if (candidates[i].id == id) {
            //  if i < k, then he either wins regardless of the other votes, or he gets in the parliament if the next ones all vote for him.
            //  otherwise, we must check if he gets in if the others all vote for him
            if (n == k) {
                if (candidates[i].votes) {
                    return 1;
                }
                if (candidates[i].votes + m - a) {
                    return 2;
                }
                return 3;
            }

            if (i < k) {
                //std::cout << "Intram aici pentru " << id << '\n';
                int needed_votes = 0;
                for (int j = 1; j <= k - i; j++) {
                    needed_votes += candidates[i].votes - candidates[i + j].votes;
                    if (candidates[i].votes != 0) {
                        needed_votes += 1;
                    }
                }

                if (candidates[i].votes == 0 && m - a == 0) {
                    return 3;
                }

                if (needed_votes > m - a) {
                    return 1;
                }
                return 2;
            } else {
                int needed = candidates[k - 1].votes - candidates[i].votes;

                if (candidates[k - 1].votes == 0) {
                    needed = 1;
                } else {
                    needed += 1;
                }

                if (needed <= m - a) {
                    return 2;
                }
                return 3;
            }
        }
    }


    return 0;
}

int main() {
    read_input();

    std::sort(candidates.begin(), candidates.end());

    for (int i = 0; i < n; i++) {
        std::cout << get_verdict(i) << " ";
    }
    std::cout << '\n';

    return 0;
}
