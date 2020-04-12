/**
  *  Worg
  */
#include <vector>
#include <cstdio>
#include <algorithm>

FILE *ffin = freopen("permutariab.in", "r", stdin);
FILE *ffout = freopen("permutariab.out", "w", stdout);

const int MAX_N = 3e5 + 5;

int n;
int a[MAX_N], b[MAX_N], where[MAX_N];
int aib[MAX_N];
const int BUFFER_SIZE = 1e5;

class InputReader {
    public:
    char buffer[BUFFER_SIZE];
    int cursor;

    void get_buffer() {
        cursor = 0;
        fread(buffer, 1, BUFFER_SIZE, stdin);
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

int lsb(int x) {
    return (x & (-x));
}

void aib_update(int position) {
    for (int i = position; i <= n; i += lsb(i)) {
        aib[i] += 1;
    }
}

int aib_query(int position) {
    int answer = 0;
    for (int i = position; i > 0; i -= lsb(i)) {
        answer += aib[i];
    }
    return answer;
}

int main(int argc, char **argv) {
    fin >> n;
    for (int i = 1; i <= n; i++) {
        fin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        fin >> b[i];
        where[b[i]] = i;
    }

    long long solution = 0;
    for (int i = n; i >= 1; i--) {
        int position = where[a[i]] - aib_query(where[a[i]] - 1);
        solution += (i - position);
        aib_update(where[a[i]]);
    }

    printf("%lld\n", solution);
    return 0;
}
