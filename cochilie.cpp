/**
 *  Worg
 */
#include <cstdio>
#include <vector>

const char FILE_IN[] = "cochilie.in";
const char FILE_OUT[] = "cochilie.out";

struct Boundary {
    int x0, y0, x1, y1;

    Boundary() {}

    Boundary(int _x0, int _y0, int _x1, int _y1) : x0(_x0), y0(_y0), x1(_x1), y1(_y1) {}
};

std::vector<Boundary> compute_boundaries(int steps) {
    std::vector<Boundary> boundaries = {{1, 1, 1, 1}};

    int h = 1, w = 1;
    for (int i = 1; i < steps; i++) {
        if (i % 4 == 1) {  //  right
            boundaries.emplace_back(1, w + 1, h, w + h);
            w += h;
        } else if (i % 4 == 2) {  //  down
            boundaries.emplace_back(h + 1, 1, h + w, w);
            h += w;
        } else if (i % 4 == 3) {  //  left
            //  add h to all the previous y coordinates
            for (Boundary& boundary : boundaries) {
                boundary.y0 += h;
                boundary.y1 += h;
            }
            boundaries.emplace_back(1, 1, h, h);
            w += h;
        } else {  //  up
            //  add w to all the previous x coordinates
            for (Boundary& boundary : boundaries) {
                boundary.x0 += w;
                boundary.x1 += w;
            }
            boundaries.emplace_back(1, 1, w, w);
            h += w;
        }
    }

    return boundaries;
}

std::vector<int> reconstruct_line(int line_id, int w, std::vector<Boundary> boundaries) {
    std::vector<int> line(w);

    for (int i = 0; i < (int)boundaries.size(); i++) {
        Boundary boundary = boundaries[i];
        if (boundary.x0 <= line_id && line_id <= boundary.x1) {
            for (int y = boundary.y0; y <= boundary.y1; y++) {
                line[y - 1] = i + 1;
            }
        }
    }

    return line;
}

int main(int argc, char **argv) {
    FILE *fp_in = fopen(FILE_IN, "r");
    FILE *fp_out = fopen(FILE_OUT, "w");

    int task, n;
    fscanf(fp_in, "%d%d", &task, &n);

    //  compute height and width of the matrix
    int h = 1, w = 1;

    for (int i = 1; i < n; i++) {
        if (i % 2 == 1) {
            w += h;
        } else {
            h += w;
        }
    }

    if (task == 1) {
        fprintf(fp_out, "%d %d\n", h, w);
    } else {
        int p;
        fscanf(fp_in, "%d", &p);

        std::vector<Boundary> boundaries = compute_boundaries(n);
        std::vector<int> line = reconstruct_line(p, w, boundaries);

        for (int& elem : line) {
            fprintf(fp_out, "%d ", elem);
        }
        fprintf(fp_out, "\n");
    }

    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
