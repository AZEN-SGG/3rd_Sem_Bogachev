#include <cstdlib>
#include <ctime>
#include <iostream>

#include "student.h"

int main(int argc, char* argv[]) {
    int task = 7;
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " r filename {name value}" << std::endl;
        return 1;
    }

    int r = atoi(argv[1]);
    const char* filename = argv[2];
    const char* name = argv[3];
    int value = atoi(argv[4]);

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        return 1;
    }

    tree a;

    if (a.read(fp) != io_status::success) return 2;
    fclose(fp);

    student stud(name, value);

    printf("Original tree:\n");
    a.print(r);
    int T = a.get_count_total();
    int L = a.get_count_leaf();
    int C1 = a.get_count_1();
    int C2 = a.get_count_2();
    int H = a.get_height();
    int W = a.get_width();
    int B = a.get_balance();
    printf(
        "%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d\n",
        argv[0], task, T, L, C1, C2, H, W, B);

    double t = clock();
    a.task7(stud);
    t = (clock() - t) / CLOCKS_PER_SEC;

    printf("Modified tree:\n");
    a.print(r);
    T = a.get_count_total();
    L = a.get_count_leaf();
    C1 = a.get_count_1();
    C2 = a.get_count_2();
    H = a.get_height();
    W = a.get_width();
    B = a.get_balance();
    printf(
        "%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d "
        "Elapsed = %.2f\n",
        argv[0], task, T, L, C1, C2, H, W, B, t);

    return 0;
}