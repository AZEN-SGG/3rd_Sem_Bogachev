#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "student.h"
#include "b_tree.h"

int main(int argc, char* argv[])
  {
  char* name = 0;
  io_status ret;
  int res;
  int m, r, k;
  double t;
  if (!(argc == 5 && sscanf(argv[1], "%d", &m) == 1 && sscanf(argv[2], "%d", &r) == 1 && sscanf(argv[3], "%d", &k) == 1 && m > 0 && r >= 0))
      {
      printf("Usage: %s m r k file\n", argv[0]);
      return -1;
      }
  name = argv[4];
  
  b_tree<student> listvennica{m};
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
        case io_status::create:
            printf("Error of linking\n");
            break;
        case io_status::open:
            printf("Error of linking\n");
            break;
        }
      return -2;
      }
  
  listvennica.print(r);
  t = clock();
  res = listvennica.solve1(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 1, m, k, res, t);
  t = clock();
  res = listvennica.solve2(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 2, m, k, res, t);
  t = clock();
  res = listvennica.solve3(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 3, m, k, res, t);
  t = clock();
  res = listvennica.solve4(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 4, m, k, res, t);
  t = clock();
  res = listvennica.solve5(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 5, m, k, res, t);
  t = clock();
  res = listvennica.solve6(k);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf ("%s : Task = %d M = %d K = %d Result = %d Elapsed = %.2f\n", argv[0], 6, m, k, res, t);
  
  return 0;
  }
  
template <class T>
io_status read_file(b_tree<T>* tree, const char* name)
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
  
