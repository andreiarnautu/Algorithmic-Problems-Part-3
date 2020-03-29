#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

ifstream in("sdo.in");
ofstream out("sdo.out");

int choose_pivot(int st, int dr) {
    return st + rand() % (dr - st + 1);
}

int partition(vector <int> &a, int st, int dr) {
    int m = choose_pivot(st, dr);
    swap(a[m], a[dr]);
    int i = st - 1, j = dr;
    while (true) {
        do
            i++;
        while (a[i] < a[dr]);
        do
            j--;
        while (a[j] > a[dr]);
        if (i < j) {
            swap(a[i], a[j]);
        }
        else
            break;
    }
    swap(a[i], a[dr]);
    return i;
}

void quickselect(vector <int> &a, int st, int dr, int k) {
    if (st > dr) {
        return;
    }
    if (st == dr) {
        out << a[st] << '\n';
        return;
    }

    int p = partition(a, st, dr);
    if (p == k) {
        out << a[p] << '\n';
        return;
    }
    else if (k < p)
        quickselect(a, st, p - 1, k);
    else
        quickselect(a, p + 1, dr, k);
}

int main() {
    int n, k;
    in >> n >> k;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        in >> a[i];
    }

    srand(time(NULL));
    quickselect(a, 0, n - 1, k - 1);
    return 0;
}
