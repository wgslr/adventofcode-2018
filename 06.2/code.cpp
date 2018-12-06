#include <iostream>
#include <cstdio>
#include <cstdlib>

const int DIM = 400;
const int COUNT = 50;
const int MAX_DIST = 10000;
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
  int result = 0;
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
      int total = 0;
      for (int i = 0; i < COUNT; ++i)
      {

        total += points[i]->dist(x, y);
      }
      if (total < MAX_DIST)
      {
        ++result;
      }
    }
  }

  printf("%d\n", result);
}
