/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *file_in = freopen("aliniere.in", "r", stdin); FILE *file_out = freopen("aliniere.out", "w", stdout);

const int MAX_K = 2e3 + 5;
const int MAX_N = 2e5 + 5;
const int BUFFER_SIZE = 1e5;

class InputReader {
    public:
    char buffer[BUFFER_SIZE];
    int cursor;

    void get_buffer() {
        cursor = 0; fread(buffer, 1, BUFFER_SIZE, stdin);
    }

    InputReader() {
        get_buffer();
    }

    bool digit(char c) {
        return '0' <= c && c <= '9';
    }

    InputReader& operator >>(int &number) {
        char sgn = '+';
        while(!digit(buffer[cursor])) {
            sgn = buffer[cursor];
            if(++cursor == BUFFER_SIZE) {
                get_buffer();
            }
        }

        number = 0;

        while(digit(buffer[cursor])) {
            number = number * 10 + buffer[cursor] - '0';
            if(++cursor == BUFFER_SIZE) {
                get_buffer();
            }
        }

        number = (sgn == '-') ? -number : number;
        return *this;
    }

    InputReader& operator >>(long long &number) {
        char sgn = '+';
        while(!digit(buffer[cursor])) {
            sgn = buffer[cursor];
            if(++cursor == BUFFER_SIZE) {
                get_buffer();
            }
        }

        number = 0;
        while(digit(buffer[cursor])) {
            number = number * 10 + buffer[cursor] - '0';
            if(++cursor == BUFFER_SIZE) {
                get_buffer();
            }
        }

        number = (sgn == '-') ? -number : number;

        return *this;
    }
} fin;

int n;
int v[MAX_N],  before[MAX_N];
std::pair<int, int> intervals[MAX_K];

void compute_before() {
    for (int i = 1; i < n; i++) {
        if (v[i - 1] <= v[i]) {
            before[i] = before[i - 1];
        } else {
            before[i] = i;
        }
    }
}

int answer_query() {
    int k; fin >> k;

    int interval_count = 0, prv = 0;
    for (int i = 0; i < k; i++) {
        int id; fin >> id;
        if (prv >= before[id]) {
            intervals[interval_count] = std::make_pair(v[prv], v[id]);
            interval_count += 1;
        }
        prv = id + 1;
    }

    if (prv >= before[n - 1]) {
        intervals[interval_count] = std::make_pair(v[prv], v[n - 1]);
        interval_count += 1;
    }

    k += 1;
    if (interval_count == 0) {
        return k;
    }

    std::sort(intervals, intervals + interval_count, [&](std::pair<int, int> a, std::pair<int, int> b) {
        if (a.second != b.second) {
            return a.second < b.second;
        } else {
            return a.first < b.first;
        }
    });

    int last_end = 0, rem = 0;
    for (int i = 0; i < interval_count; i++) {
        if (intervals[i].first >= last_end) {
            rem += 1;
            last_end = intervals[i].second;
        }
    }

    return k - rem;
}

int main(int argc, char** argv) {
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> v[i];
    }

    compute_before();

    int q; fin >> q;
    for (int i = 0; i < q; i++) {
        printf("%d\n", answer_query());
    }
    return 0;
}
