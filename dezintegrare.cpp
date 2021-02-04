/**
  *  Worg
  */
#include <vector>
#include <fstream>
#include <algorithm>

std::ifstream fin("dezintegrare.in");
std::ofstream fout("dezintegrare.out");

struct Line {
    long long a, b;
    int index;

    Line() {}

    bool operator <(const Line &other) const {
        if (this->a != other.a) {
            return this->a > other.a;
        }
        return this->b < other.b;
    }
};

int n, q;
std::vector<Line> lines;
std::vector<std::pair<long long, int> > queries;

std::vector<int> stack, answer;

bool intersection(Line a, Line b, Line c) {
    return (c.b - a.b) * (b.a - c.a) < (c.b - b.b) * (a.a - c.a);
}

void read_data() {
    fin >> n >> q;
    lines.resize(n);
    answer.resize(q);
    queries.resize(q);

    for (int i = 0; i < n; i++) {
        fin >> lines[i].b >> lines[i].a;
        lines[i].a *= -1;
        lines[i].index = i + 1;
    }
    for (int i = 0; i < q; i++) {
        fin >> queries[i].first;
        queries[i].second = i;
    }
}

void compute_answer() {
    std::sort(lines.begin(), lines.end());

    for (int i = 0; i < n; i++) {
        int size = (int)stack.size();
        while (size > 1 && intersection(lines[i], lines[stack[size - 1]], lines[stack[size - 2]])) {
            stack.pop_back();
            size--;
        }
        stack.push_back(i);
    }

    std::sort(queries.begin(), queries.end());

    int stack_index = 0;
    for (std::pair<long long, int> query : queries) {
        long long time = query.first;
        int query_index = query.second;

        while (stack_index + 1 < (int)stack.size() && time * lines[stack[stack_index]].a + lines[stack[stack_index]].b >
                                                      time * lines[stack[stack_index + 1]].a + lines[stack[stack_index + 1]].b) {

            stack_index++;
        }

        answer[query_index] = lines[stack[stack_index]].index;
    }
}

void print_answer() {
    for (int& x : answer) {
        fout << x << '\n';
    }
}

int main(int argc, char **argv) {
    read_data();
    compute_answer();
    print_answer();
    return 0;
}
