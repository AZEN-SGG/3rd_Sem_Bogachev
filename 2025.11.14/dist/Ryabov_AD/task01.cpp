#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "io_status.h"
#include "solve.h"

int main(int argc, char * argv[]){
    char *name = argv[0];
    int r;
    double t;
    io_status ret;
    tree yolka;
    FILE *fp;
    if (!(argc == 3 && sscanf(argv[1], "%d", &r) == 1)){
        printf("Usage %s\n", argv[0]);
        return 1;
    }
    name = argv[2];
    if (!(fp = fopen(name, "r"))){
        printf("Cannot open %s", name);
        return 1;
    }
    ret = yolka.read(fp, -1);
    fclose(fp);
    if (ret != io_status::success){
        switch (ret){
            case io_status::no_open:
                printf("Cannot open %s", name);
                break;
            case io_status::format:
                printf("Cannot read %s", name);
                break;
            case io_status::eof:
                printf("Empty file %s", name);
                break;
            case io_status::memory:
                printf("Memory %s", name);
                break;
            case io_status::success:
                // Никогда не сработает, но иначе компилятор не пропускает
                printf("Success %s", name);
                break;
        }
        return 3;
    }
    //
    printf ("Original tree:\n");
    yolka.print(r, stdout);
    int T = yolka.get_count_total ();
    int L = yolka.get_count_leaf ();
    int C1 = yolka.get_count_1 ();
    int C2 = yolka.get_count_2 ();
    int H = yolka.get_height ();
    int W = yolka.get_width ();
    int B = yolka.get_balance ();
    printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d\n", argv[0], 1, T, L, C1, C2, H, W, B);
    t = clock ();
    yolka.task01();
    t = (clock() - t)/CLOCKS_PER_SEC;
    printf ("Modified tree:\n");
    yolka.print(r, stdout);
    T = yolka.get_count_total ();
    L = yolka.get_count_leaf ();
    C1 = yolka.get_count_1 ();
    C2 = yolka.get_count_2 ();
    H = yolka.get_height ();
    W = yolka.get_width ();
    B = yolka.get_balance ();
    printf ("%s : Task = %d T = %d L = %d C1 = %d C2 = %d H = %d W = %d B = %d Elapsed = %.2f\n", argv[0], 1, T, L, C1, C2, H, W, B, t);
    //
    return 0;
}
