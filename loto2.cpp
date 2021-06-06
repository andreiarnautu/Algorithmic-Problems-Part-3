/**
 *  Worg
 */
#include <cstdio>
#include <cstdlib>
#include <algorithm>

const char FILE_IN[] = "loto2.in";
const char FILE_OUT[] = "loto2.out";

int n;
int* arr;

void read_data() {
    FILE* fp_in = fopen(FILE_IN, "r");
    fscanf(fp_in, "%d", &n);
    arr = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(fp_in, "%d", &arr[i]);
    }
    fclose(fp_in);
}

bool check(int x) {
    for (int i = n - 1; i >= 0; i--) {
        if (x % arr[i] == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    read_data();

    int answer = 0;
    for (int i = 0; i < n; i++) {
        answer = std::max(answer, arr[i]);
    }

    do {
        answer++;
    } while (!check(answer));

    FILE* fp_out = fopen(FILE_OUT, "w");
    fprintf(fp_out, "%d\n", answer);
    fclose(fp_out);
    return 0;
}
