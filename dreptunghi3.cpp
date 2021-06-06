/**
 *  Worg
 */
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>

const char* FILE_IN = "dreptunghi3.in";
const char* FILE_OUT = "dreptunghi3.out";

class Node {
public:
    Node* left_son;
    Node* right_son;

    char operation_type;
    int operation_number;

    Node() : left_son(NULL), right_son(NULL), operation_type('*'), operation_number(0) {

    }
};

class Solver {
public:
    Solver(const char* input_path, const char* output_path) {
        fin = std::ifstream(input_path);
        fout = std::ofstream(output_path);
    }

    void read_data() {
        fin >> task >> code;
    }

    void parse_code() {
        int cursor = 0;
        parse(root, cursor);
    }

    void compute_catalan() {
        catalan.resize((int)code.size());
        catalan[0] = 1;

        for (int i = 1; i < (int)catalan.size(); i++) {
            catalan[i] = 0;
            for (int j = 0; j < i; j++) {
                catalan[i] += 1LL * catalan[j] * catalan[i - j - 1] % MOD;
                catalan[i] %= MOD;
            }
        }
    }

    void solve_task() {
        switch (task) {
            case 1: {
                fout << count_leaves(root) << '\n';
                break;
            }

            case 2: {
                std::pair<int, int> size = compute_minimum_size();
                fout << size.first << ' ' << size.second << '\n';
                break;
            }

            case 3: {
                fout << count_equivalent_codes() << '\n';
                break;
            }

            case 4: {
                dfs_rearrange(root);
                dfs_print(root);
                fout << '\n';
                break;
            }
        }
    }

private:
    static const int MOD = 1e9 + 7;

    std::ifstream fin;
    std::ofstream fout;

    int task;
    std::string code;
    Node* root;
    std::vector<int> catalan;

    bool is_digit(char c) {
        return '0' <= c && c <= '9';
    }

    void parse(Node*& node, int& cursor) {
        node = new Node();

        if (code[cursor] == '*') {
            //  end of recursion
            cursor++;
            return;
        } else {
            node->operation_type = code[cursor];
            node->operation_number = 0;

            cursor++;
            while (is_digit(code[cursor])) {
                node->operation_number = node->operation_number * 10 + code[cursor] - '0';
                cursor++;
            }
            //  continue recursion
            parse(node->left_son, cursor);
            parse(node->right_son, cursor);
        }
    }

    int count_leaves(Node* node) {
        if (node->left_son == NULL) {
            return 1;
        }

        return count_leaves(node->left_son) + count_leaves(node->right_son);
    }

    std::pair<int, int> compute_minimum_size() {
        int max_h = 0;
        int max_w = 0;
        dfs_hw(root, 0, 0, max_h, max_w);
        return {max_h, max_w};
    }

    void dfs_hw(Node* node, int crt_h, int crt_w, int& max_h, int& max_w) {
        int new_h = crt_h;
        int new_w = crt_w;

        if (node->operation_type == 'H') {
            new_h += node->operation_number;
        } else if (node->operation_type == 'V') {
            new_w += node->operation_number;
        }

        max_h = std::max(max_h, new_h + 1);
        max_w = std::max(max_w, new_w + 1);

        if (node->operation_type != '*') {
            dfs_hw(node->left_son, crt_h, crt_w, max_h, max_w);
            dfs_hw(node->right_son, new_h, new_w, max_h, max_w);
        }
    }

    void dfs_comp(Node* node, int& size, std::queue<Node*>& queue) {
        size++;

        if (node->left_son->operation_type == node->operation_type) {
            dfs_comp(node->left_son, size, queue);
        } else if (node->left_son->operation_type != '*') {
            queue.push(node->left_son);
        }

        if (node->right_son->operation_type == node->operation_type) {
            dfs_comp(node->right_son, size, queue);
        } else if (node->right_son->operation_type != '*') {
            queue.push(node->right_son);
        }
    }

    int count_equivalent_codes() {
        std::queue<Node*> queue;
        if (root->operation_type != '*') {
            queue.push(root);
        }

        int answer = 1;
        while (!queue.empty()) {
            Node* comp_root = queue.front();
            queue.pop();

            int size = 0;
            dfs_comp(comp_root, size, queue);

            answer = 1LL * answer * catalan[size] % MOD;
        }

        return answer;
    }

    void dfs_rearrange(Node*& node) {
        if (node->operation_type == '*') return;

        if (node->operation_type == node->left_son->operation_type) {
            node->operation_number -= node->left_son->operation_number;

            Node* new_node= node->left_son;
            node->left_son = new_node->right_son;
            new_node->right_son = node;
            node = new_node;

            dfs_rearrange(node);
        } else {
            dfs_rearrange(node->left_son);
            dfs_rearrange(node->right_son);
        }
    }

    void dfs_print(Node* node) {
        fout << node->operation_type;

        if (node->operation_type != '*') {
            fout << node->operation_number;
            dfs_print(node->left_son);
            dfs_print(node->right_son);
        }
    }
};

int main() {
    Solver solver(FILE_IN, FILE_OUT);
    solver.read_data();
    solver.parse_code();
    solver.compute_catalan();
    solver.solve_task();
    return 0;
}
