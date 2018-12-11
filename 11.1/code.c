#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long SERIAL = 1133;
// const long SERIAL = 18;
// const long SERIAL = 8;
const long DIM = 301;

int main()
{
  long LEVELS[DIM][DIM];
  long SUMS[DIM][DIM];

  memset(SUMS, 0, sizeof(SUMS));
  memset(LEVELS, 0, sizeof(LEVELS));

  long bests = -1000000;
  long bestx = -1;
  long besty = -1;

  for (int x = 1; x < DIM; ++x)
  {
    for (int y = 1; y < DIM; ++y)
    {
      long rackid = x + 10;
      LEVELS[x][y] = (rackid * y + SERIAL) * rackid;
      LEVELS[x][y] = LEVELS[x][y] % 1000 / 100 - 5;

      for (int sx = x - 2; sx <= x; sx++)
      {
        for (int sy = y - 2; sy <= y; sy++)
        {
          if (sx < 1 || sy < 1)
          {
            continue;
          }
          SUMS[sx][sy] += LEVELS[x][y];
        }
      }
      if (x >= 3 && y >= 3 && SUMS[x - 2][y - 2] > bests)
      {
        bests = SUMS[x - 2][y - 2];
        bestx = x - 2;
        besty = y - 2;
      }
    }
  }

  printf("%ld,%ld %ld\n", bestx, besty, bests);

  return 0;
}
