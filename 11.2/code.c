#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long SERIAL = 1133;
// const long SERIAL = 18;
// const long SERIAL = 8;
const long DIM = 301;

long min(long x, long y)
{
  return x < y ? x : y;
}

long max(long x, long y)
{
  return x > y ? x : y;
}

int main()
{
  int LEVELS[DIM][DIM];

  /**
   * Third dimension is the square.
   * During summation only the right and bottom border of the square is counted.
   * Rest can be derived by summing smaller sizes
   */
  long **SUMS[DIM];
  for (int i = 0; i < DIM; ++i)
  {
    SUMS[i] = calloc(DIM, sizeof(long *));
    for (int j = 0; j < DIM; ++j)
    {
      SUMS[i][j] = calloc(DIM, sizeof(long));
    }
  }

  memset(LEVELS, 0, sizeof(LEVELS));

  long bests = -1000000;
  long bestx = -1;
  long besty = -1;
  long bestd = -1;
  long rackid;

  for (int x = 1; x < DIM; ++x)
  {
    for (int y = 1; y < DIM; ++y)
    {
      rackid = x + 10;
      LEVELS[x][y] = (rackid * y + SERIAL) * rackid;
      LEVELS[x][y] = LEVELS[x][y] % 1000 / 100 - 5;

      for (int sx = 1; sx <= x; sx++)
      {
        for (int sy = 1; sy <= y; sy++)
        {
          int dim = max(x - sx, y - sy) + 1;
          SUMS[sx][sy][dim] += LEVELS[x][y];
        }
      }
    }
  }

  for (int x = 1; x < DIM; ++x)
  {
    for (int y = 1; y < DIM; ++y)
    {
      for (int d = 1; d < DIM; ++d)
      {
        SUMS[x][y][d] += SUMS[x][y][d - 1];

        if (SUMS[x][y][d] > bests)
        {
          bests = SUMS[x][y][d];
          bestx = x;
          besty = y;
          bestd = d;
        }
      }
    }
  }

  printf("%ld,%ld,%ld %ld\n", bestx, besty, bestd, bests);

  return 0;
}
