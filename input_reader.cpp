const BUFFER_SIZE = 1e5;

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
};
