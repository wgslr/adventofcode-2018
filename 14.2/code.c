#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

const int INPUT_DIGITS[] = {1, 1, 0, 2, 0, 1};
const int INPUT_LEN = 6;

int length = 0;

typedef struct list
{
  int val;
  struct list *next;
  struct list *prev;
} list;

// returns pointer to the new element
list *insert_after(list *l, int val)
{
  list *n = calloc(1, sizeof(list));
  n->val = val;
  n->next = l->next;
  l->next = n;

  n->next->prev = n;
  n->prev = l;

  return n;
}

list *steps(list *from, int count)
{
  for (int i = 0; i < count; ++i)
  {
    from = from->next;
  }
  return from;
}

void *add_score(list **rightmost, int val)
{
  int dec = val / 10;
  int unit = val % 10;
  if (dec)
  {
    *rightmost = insert_after(*rightmost, dec);
    ++length;
  }
  *rightmost = insert_after(*rightmost, unit);
  ++length;
}

bool stop(list *rightmost)
{
  for (int i = 0; i < INPUT_LEN; ++i)
  {
    if (rightmost->val != INPUT_DIGITS[INPUT_LEN - i - 1])
      return false;
    rightmost = rightmost->prev;
  }
  return true;
}

int main()
{
  list *leftmost = calloc(1, sizeof(list));
  leftmost->prev = leftmost;
  leftmost->next = leftmost;
  leftmost->val = 3;

  list *elf1, *elf2;

  elf1 = leftmost;
  elf1->next = elf1; // circle
  elf1->prev = elf1; // circle

  elf2 = insert_after(elf1, 7);
  list *rightmost = elf2;
  length = 2;

  int generation = 1;
  while (!stop(rightmost) && !stop(rightmost->prev))
  {
    ++generation;

    int to_add = elf1->val + elf2->val;
    add_score(&rightmost, to_add);
    elf1 = steps(elf1, 1 + elf1->val);
    elf2 = steps(elf2, 1 + elf2->val);
  }

  if (stop(rightmost))
  {
    printf("last matched: %d\n", length - INPUT_LEN);
  }
  else if (stop(rightmost->prev))
  {
    printf("previous matched: %d\n", length - INPUT_LEN - 1);
  }

  return 0;
}