
/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <fstream>
#include <algorithm>

FILE *fin = freopen("zone.in", "r", stdin); FILE *fout = freopen("zone.out", "w", stdout);

const int ZONE_COUNT = 9;
const int MAX_N = 500 + 1;
int n;
std::map<long long, int> exists;
std::vector<long long> zone_sums(ZONE_COUNT);
long long sum[MAX_N][MAX_N];

const int kBufferSize = 1e5;

class InputReader {
public:
    char buffer[kBufferSize];
    int cursor;

    void getBuffer() {
        cursor = 0; fread(buffer, 1, kBufferSize, stdin);
    }

    InputReader() {
        getBuffer();
    }

    bool digit(char c) {
        return '0' <= c && c <= '9';
    }

    InputReader& operator >>(int &number) {
        char sgn = '+';
        while(!digit(buffer[cursor])) {
            sgn = buffer[cursor];
            if(++cursor == kBufferSize) {
                getBuffer();
            }
        }

        number = 0;
        while(digit(buffer[cursor])) {
            number = number * 10 + buffer[cursor] - '0';
            if(++cursor == kBufferSize) {
                getBuffer();
            }
        }

        number = (sgn == '-') ? -number : number;

        return *this;
    }

    InputReader& operator >>(long long &number) {
        char sgn = '+';
        while(!digit(buffer[cursor])) {
            sgn = buffer[cursor];
            if(++cursor == kBufferSize) {
                getBuffer();
            }
        }

        number = 0;
        while(digit(buffer[cursor])) {
            number = number * 10 + buffer[cursor] - '0';
            if(++cursor == kBufferSize) {
                getBuffer();
            }
        }

        number = (sgn == '-') ? -number : number;

        return *this;
    }
} cin;


void read_data() {
    cin >> n;
    for (auto& num: zone_sums) {
        cin >> num;
        exists[num] = 1;
    }
    std::sort(zone_sums.begin(), zone_sums.end());

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; cin >> x;
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + x;
        }
    }
}

std::vector<long long> make_zone_sums(int i, int j, int x, int y) {
    std::vector<long long> ret(9);
    ret[0] = sum[i][j];
    ret[1] = sum[i][y] - ret[0];
    ret[2] = sum[i][n] - ret[1] - ret[0];

    ret[3] = sum[x][j] - ret[0];
    ret[4] = sum[x][y] - ret[3] - ret[1] - ret[0];
    ret[5] = sum[x][n] - ret[4] - ret[3] - ret[2] - ret[1] - ret[0];

    ret[6] = sum[n][j] - ret[3] - ret[0];
    ret[7] = sum[n][y] - ret[6] - ret[4] - ret[3] - ret[1] - ret[0];
    ret[8] = sum[n][n] - ret[7] - ret[6] - ret[5] - ret[4] - ret[3] - ret[2] - ret[1] - ret[0];

    std::sort(ret.begin(), ret.end());
    return ret;
}

bool equal_arrays(std::vector<long long>& a, std::vector<long long> &b) {
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> compute_answer() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (exists[sum[i][j]]) {
                for (int x = i + 1; x < n; x++) {
                    if (exists[sum[x][j] - sum[i][j]]) {
                        for (int y = j + 1; y < n; y++) {
                            if (exists[sum[i][y] - sum[i][j]]) {
                                std::vector<long long> v = make_zone_sums(i, j, x, y);
                                if (equal_arrays(v, zone_sums)) {
                                    return {i, x, j, y};
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return {-1, -1, -1, -1};
}

int main(int argc, char const *argv[]) {
    read_data();
    std::vector<int> answer = compute_answer();
    for (auto& num : answer) {
        printf("%d ", num);
    }
    printf("\n");
    return 0;
}
