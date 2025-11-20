#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tree.h"

int main(int argc, char* argv[])
  {
  char* name = 0;
  tree listvennica;
  io_status ret;
  int res;
  int p, k;
  double t;
  if (!(argc == 4 && sscanf(argv[1], "%d", &p) == 1 && sscanf(argv[3], "%d", &k) == 1))
      {
      printf("Usage: %s p file k\n", argv[0]);
      return -1;
      }
  name = argv[2];
  ret = read_file(&listvennica, name);
  if (ret != io_status::success)
      {
      switch (ret)
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
  printf("Initial tree:\n");
  listvennica.print(p);
  t = clock();
  res = listvennica.solve1(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 1, k, res, t);
  t = clock();
  res = listvennica.solve2(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 2, k, res, t);
  t = clock();
  res = listvennica.solve3(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 3, k, res, t);
  t = clock();
  res = listvennica.solve4(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 4, k, res, t);
  t = clock();
  res = listvennica.solve5(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 5, k, res, t);
  t = clock();
  res = listvennica.solve6(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 6, k, res, t);
  t = clock();
  res = listvennica.solve7(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d k = %d Result = %d Elapsed = %.2f\n", argv[0], 7, k, res, t);
  printf("New tree:\n");
  listvennica.print(p);
  return 0;
  }
  

