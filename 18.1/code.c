#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

const int LIMIT = 10;
const int WIDTH = 50;
const int HEIGHT = 50;

typedef enum
{
  GROUND,
  TREE,
  YARD
} field;

void load(field state[HEIGHT][WIDTH])
{
  char line[WIDTH];
  for (int y = 0; y < HEIGHT; ++y)
  {
    scanf("%s\n", line);
    for (int x = 0; x < WIDTH; ++x)
    {
      switch (line[x])
      {
      case '.':
        state[y][x] = GROUND;
        break;
      case '|':
        state[y][x] = TREE;
        break;
      case '#':
        state[y][x] = YARD;
        break;
      default:
        fprintf(stderr, "Unexpected symbol %c\n", line[x]);
      }
    }
  }
}

void display(field state[HEIGHT][WIDTH])
{
  for (int y = 0; y < HEIGHT; ++y)
  {
    for (int x = 0; x < WIDTH; ++x)
    {
      switch (state[y][x])
      {
      case GROUND:
        printf(".");
        break;
      case TREE:
        printf("|");
        break;
      case YARD:
        printf("#");
        break;
      }
    }
    printf("\n");
  }
}

int main()
{
  field state[2][HEIGHT][WIDTH];

  load(state[0]);
  display(state[0]);

  return 0;
}