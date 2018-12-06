#include <iostream>
#include <cstdio>
#include <cstdlib>

const int DIM = 400;
const int COUNT = 50;
// const int COUNT = 6;

class Point
{
public:
  int id;
  int x;
  int y;
  int area = 0;

  Point(int x, int y, int id)
  {
    this->x = x;
    this->y = y;
    this->id = id;
  }

  int dist(Point &other)
  {
    return abs(this->x - other.x) + abs(this->y - other.y);
  }

  int dist(int x, int y)
  {
    return abs(this->x - x) + abs(this->y - y);
  }
};

int main()
{
  int x, y;

  Point *points[COUNT];
  int owner[DIM][DIM] = {0};
  int i = 0;

  while (scanf("%d, %d", &y, &x) != EOF)
  {
    Point *p = new Point(x, y, i);
    points[i++] = p;
  }

  fprintf(stderr, "Read input\n");

  for (int x = 0; x < DIM; ++x)
  {
    for (int y = 0; y < DIM; ++y)
    {
      int minid = -1;
      int mindist = DIM * 2;

      for (int i = 0; i < COUNT; ++i)
      {
        const int dist = points[i]->dist(x, y);
        // fprintf(stderr, "Dist (%d, %d) to (%d, %d): %d\n", x, y, points[i]->x, points[i]->y, dist);
        if (dist < mindist)
        {
          minid = points[i]->id;
          mindist = dist;
        }
        else if (dist == mindist)
        {
          // two or more equally distant
          minid = -1;
        }
      }

      if (minid >= 0)
      {
        owner[x][y] = points[minid]->id;
        points[minid]->area++;

        printf("%2d ", owner[x][y]);
      }else {

        printf(".  ");
      }
    }
    printf("\n");
  }

  fprintf(stderr, "Calculated closest\n");

  for (int x = 0; x < DIM; ++x)
  {
    for (int y = 0; y < DIM; ++y){
      if ((x != 0 && x != DIM - 1 && y != 0 && y != DIM - 1) || owner[x][y] < 0)
      {
        continue;
      }

      fprintf(stderr, "%d %d disqualified: %d\n", x, y, owner[x][y]);
      fprintf(stderr, "%d disqualified\n", points[owner[x][y]]->id);
      points[owner[x][y]]->area = -1;
    }
  }

  int best = 0;
  int bestid = 0;
  for (int i = 0; i < COUNT; ++i)
  {
    if (points[i]->area > best)
    {
      bestid = points[i]->id;
      best = points[i]->area;
    }
  }

  printf("%d is best: %d\n", bestid, best);

  return 0;
}
