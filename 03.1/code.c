#include <stdio.h>
#include <string.h>

const int DIM = 1000;

int main() {
  // allowed values:
  // \0 - not taken
  // 'o' - taken once
  // 'm' - taken multiple times
  char status[DIM][DIM];
  memset(status, 0, sizeof(status));

  int id,l, t, w, h;
  int overlaps = 0;
  while(scanf("#%d @ %d,%d: %dx%d\n",&id, &l, &t, &w, &h) != EOF){
    for(int x = l; x < l + w; ++x){
      for(int y = t; y < t + h; ++y) {
        switch (status[x][y]) {
          case 0:
            status[x][y] = 'o';
            break;
          case 'o':
            status[x][y] = 'm';
            ++overlaps;
            break;
        }
      }
    }
  } 

  printf("%d\n", overlaps);
}