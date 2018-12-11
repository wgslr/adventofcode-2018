#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long SERIAL = 1133;
// const long SERIAL = 8;
const int DIM = 301;

int main()
{
  long LEVELS[DIM][DIM];
  long SUMS[DIM][DIM];

  memset(SUMS, 0, sizeof(SUMS));
  int bests = 0;
  int bestx;
  int besty;

  for (int x = 1; x < DIM; ++x)
  {
    for (int y = 1; y < DIM; ++y)
    {
      int rackid = x + 10;
      LEVELS[x][y] = (rackid * y + SERIAL) * rackid;
      LEVELS[x][y] = LEVELS[x][y] % 1000 / 100 - 5;

      if (x >= 3 && y >= 3)
      {
        SUMS[x - 2][y - 2] += LEVELS[x][y];

        if (SUMS[x - 2][y - 2] > bests)
        {
          bests = SUMS[x - 2][y - 2];
          bestx = x;
          besty = y;
        }
      }
    }
  }

  // for(int i = 0; )

  printf("%d,%d %d", bestx, besty, bests);
}
