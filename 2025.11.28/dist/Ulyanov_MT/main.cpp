#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"
#include "list.h"
#include "tree.h"

int list2::m = 0;
int list2::r = 0;

int main(int argc, char* argv[])
  {
  char* name = 0;
  io_status ret1;
  io_status ret2;
  int res;
  int mp, rp;
  double t;
  if (!(argc == 4 && sscanf(argv[1], "%d", &rp) == 1 && sscanf(argv[3], "%d", &mp) == 1 && mp > 0 && rp >= 0))
      {
      printf("Usage: %s r file m\n", argv[0]);
      return -1;
      }
  name = argv[2];
  list2::set_m(mp);
  list2::set_r(rp);
  
  tree<student> listvennica;
  ret1 = read_file(&listvennica, name);
  if (ret1 != io_status::success)
      {
      switch (ret1)
        {
        case io_status::success:
            break;
        case io_status::eof:
            printf("Can not open %s\n", name);
            break;
        case io_status::format:
            printf("Can not read %s\n", name);
            break;
        case io_status::memory:
            printf("Not enough memory\n");
            break;
        }
      return -2;
      }
  
  printf("Original tree:\n");
  listvennica.print(rp);
  t = clock();
  res = listvennica.solve1();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 1, mp, res, t);
  t = clock();
  res = listvennica.solve2();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 2, mp, res, t);
  t = clock();
  res = listvennica.solve3();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 3, mp, res, t);
  t = clock();
  res = listvennica.solve4();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 4, mp, res, t);
  t = clock();
  res = listvennica.solve5();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 5, mp, res, t);
  t = clock();
  res = listvennica.solve6();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 6, mp, res, t);
  printf("Modified tree:\n");
  listvennica.print(rp);
  
  tree<list2> yggdrasil;
  ret2 = read_file(&yggdrasil, name);
  if (ret2 != io_status::success)
      {
      switch (ret2)
        {
        case io_status::success:
            break;
        case io_status::eof:
            printf("Can not open %s\n", name);
            break;
        case io_status::format:
            printf("Can not read %s\n", name);
            break;
        case io_status::memory:
            printf("Not enough memory\n");
            break;
        }
      return -2;
      }
  
  printf("\n");
  printf("Original tree:\n");
  yggdrasil.print(rp);
  t = clock();
  res = yggdrasil.solve1();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 1, mp, res, t);
  t = clock();
  res = yggdrasil.solve2();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 2, mp, res, t);
  t = clock();
  res = yggdrasil.solve3();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 3, mp, res, t);
  t = clock();
  res = yggdrasil.solve4();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 4, mp, res, t);
  t = clock();
  res = yggdrasil.solve5();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 5, mp, res, t);
  t = clock();
  res = yggdrasil.solve6();
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d Result = %d Elapsed = %.2f\n", argv[0], 6, mp, res, t);
  printf("Modified tree:\n");
  yggdrasil.print(rp);
  
  return 0;
  }
  
template <class T>
io_status read_file(tree<T>* tree, const char* name)
    {
    FILE *fp;
    io_status ret;
    fp = fopen(name, "r");
    if (!fp)
        return io_status::eof;
    ret = tree->read(fp);
    fclose(fp);
    return ret;
    }
  
