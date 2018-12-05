#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

const int DIM = 1000;
const int MAX_ID = 1233;

typedef struct list
{
  int val;
  struct list *next;
} list;

void push(list **l, int val)
{
  list *n = calloc(1, sizeof(list));
  n->next = *l;
  n->val = val;
  *l = n;
}

int main()
{
  // allowed values:
  // \0 - not taken
  // 'o' - taken once
  // 'm' - taken multiple times
  char status[DIM][DIM];
  memset(status, 0, sizeof(status));

  int id, l, t, w, h;
  int overlaps = 0;
  bool claim_ok[MAX_ID + 1];
  memset(claim_ok, 1, sizeof(claim_ok));

  list **claims_in_field[DIM];
  
  for(int i = 0; i < DIM; ++i){
    claims_in_field[i] = calloc(sizeof(list *), DIM );
  }

  while (scanf("#%d @ %d,%d: %dx%d\n", &id, &l, &t, &w, &h) != EOF)
  {
    for (int x = l; x < l + w; ++x)
    {
      for (int y = t; y < t + h; ++y)
      {
        push(&claims_in_field[x][y], id);
        switch (status[x][y])
        {
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

  for (int x = 0; x < DIM; ++x)
  {
    for (int y = 0; y < DIM; ++y)
    {
      if(status[x][y] == 'm'){
        list * l = claims_in_field[x][y];
        while(l != 0) {
          claim_ok[l->val] = false;
          l = l->next;
        }
      }
    }
  }

  for(int i = 1; i < MAX_ID; ++i){
    if(claim_ok[i]) {
      printf("%d\n", i);
    }
  }
}