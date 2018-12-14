#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// const int INPUT = 110201;
const int INPUT = 110201;
// const int INPUT = 9;

int generated = 0;

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

// returns pointer to the new element
list *insert_after(list *l, int val)
{
  list *n = calloc(1, sizeof(list));
  n->val = val;
  n->next = l->next;
  l->next = n;
  // fprintf(stderr, "add %d after %d\n", n->val, l->val);
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
    ++generated;
  }
  *rightmost = insert_after(*rightmost, unit);
  ++generated;
}

void print_all(list *leftmost, list *elf1, list *elf2)
{
  list *it = leftmost;
  do
  {
    if (it == elf1)
    {
      printf("(%d)", it->val);
    }
    else if (it == elf2)
    {
      printf("[%d]", it->val);
    }
    else
    {
      printf(" %d ", it->val);
    }
    it = it->next;
  } while (it != leftmost);
  printf("\n");
}

int main()
{
  list *leftmost;
  push(&leftmost, 3);
  list *elf1 = leftmost;
  elf1->next = elf1; // circle
  list *elf2 = insert_after(elf1, 7);
  list *rightmost = elf2;
  generated = 0;

  while (generated < INPUT + 10)
  {
    // print_all(leftmost, elf1, elf2);
    int to_add = elf1->val + elf2->val;
    add_score(&rightmost, to_add);
    elf1 = steps(elf1, 1 + elf1->val);
    elf2 = steps(elf2, 1 + elf2->val);
  }

  list *result = steps(leftmost, INPUT);
  for (int i = 0; i < 10; ++i)
  {
    printf("%d", result->val);
    result = result->next;
  }
  printf("\n");

  return 0;
}