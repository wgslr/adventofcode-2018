#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#ifdef TEST
const int WIDTH = 10;
const int HEIGHT = 10;
#else
const int WIDTH = 50;
const int HEIGHT = 50;
#endif

const int LIMIT = 10;

typedef enum { GROUND, TREE, YARD } field;

int max(const int x, const int y) { return x > y ? x : y; }

int min(const int x, const int y) { return x < y ? x : y; }

void load(field state[HEIGHT][WIDTH]) {
  char line[WIDTH];
  for (int y = 0; y < HEIGHT; ++y) {
    scanf("%s\n", line);
    for (int x = 0; x < WIDTH; ++x) {
      switch (line[x]) {
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

void display(const field state[HEIGHT][WIDTH]) {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      switch (state[y][x]) {
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

bool enough(const field type, const int required, const int x, const int y,
            const field state[HEIGHT][WIDTH]) {
  int count = 0;
  for (int yy = max(y - 1, 0); yy <= min(y + 1, HEIGHT - 1); yy++) {
    for (int xx = max(x - 1, 0); xx <= min(x + 1, HEIGHT - 1); xx++) {
      if (xx == x && yy == y) {
        continue;
      }

      if (state[yy][xx] == type) {
        ++count;
        if (count >= required)
          return true;
      }
    }
  }
  return false;
}

void tick(const field before[HEIGHT][WIDTH], field after[HEIGHT][WIDTH]) {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      switch (before[y][x]) {
      case GROUND:
        if (enough(TREE, 3, x, y, before)) {
          after[y][x] = TREE;
        } else {
          after[y][x] = GROUND;
        }
        break;
      case TREE:
        if (enough(YARD, 3, x, y, before)) {
          after[y][x] = YARD;
        } else {
          after[y][x] = TREE;
        }
        break;
      case YARD:
        if (enough(YARD, 1, x, y, before) && enough(TREE, 1, x, y, before)) {
          after[y][x] = YARD;
        } else {
          after[y][x] = GROUND;
        }
        break;
      default:
        fprintf(stderr, "Unexpected before[%d][%d]: %d\n", y, x, before[y][x]);
        assert(false);
      }
    }
  }
}

int score(field state[HEIGHT][WIDTH]) {
  int yards = 0;
  int trees = 0;
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (state[y][x] == TREE) {
        trees++;
      } else if (state[y][x] == YARD) {
        ++yards;
      }
    }
  }
  return yards * trees;
}

int main() {
  field state[2][HEIGHT][WIDTH];

  load(state[0]);
  // display(state[0]);

  int curr, prev;
  prev = 1;
  curr = 0;
  for (int i = 0; i < LIMIT; ++i) {
    curr = !curr;
    prev = !prev;
    tick(state[prev], state[curr]);
  }
  display(state[curr]);

  printf("%d\n", score(state[curr]));

  return 0;
}