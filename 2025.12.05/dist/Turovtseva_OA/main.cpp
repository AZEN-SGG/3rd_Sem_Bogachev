#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"
#include "btree.h"

int main (int argc, char *argv[])
{
    int m, r, k;
    // Ввод аргументов командной строки
    if(!(argc==5 && sscanf(argv[1],"%d",&m)==1 &&
    sscanf(argv[2],"%d",&r)==1 &&
    sscanf(argv[3],"%d",&k)==1 && m>=1))
    {
        printf("%s:Usage: m r k filenme\n",argv[0]);
        return -1;
    }
    
    char *filename = argv[4];
    FILE *fp;
    fp = fopen(filename,"r");
    if(!fp)
    {
        printf("smth wrong with %s in %s",filename, argv[0]);
        return -2;
    }

    b_tree<student> *a = new b_tree<student>(m);
    // Работа с деревом b_tree<student>
    io_status ret = a->read(fp);
    fclose(fp);
    do
    {
        switch(ret)
        {
            case io_status::success:
                continue;
            case io_status::eof:
                printf("%s : eof\n", argv[0]);
                break;
            case io_status::format:
                printf("%s : format\n", argv[0]);
                break;
            case io_status::memory:
                printf("%s : mem\n", argv[0]);
                break;
            case io_status::create:
                printf("%s : create??\n", argv[0]);
                break;
        }
        delete a;
        return -3;
    }while (0);
    a->print(r);
    
    double t=clock();
    int res = a->solve_1(k);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 1, m, k, res, t);
    
    t=clock();
    res = a->solve_2(k);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 2, m, k, res, t);

    t=clock();
    res = a->solve_3(k);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 3, m, k, res, t);

    t=clock();
    res = a->solve_4(k);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 4, m, k, res, t);

    t=clock();
    res = a->solve_5(k);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 5, m, k, res, t);

    t=clock();
    res = a->solve_6(k);
    t=(clock()-t)/CLOCKS_PER_SEC;
    printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 6, m, k, res, t);
    
    delete a;
    return 0;
}
