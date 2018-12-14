#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// const int INPUT = 110201;
// const int INPUT = 2118;
const int INPUT_DIGITS[] = {1, 1, 0, 2, 0, 1};
const int INPUT_LEN = 6;
// const int INPUT_DIGITS[] = {5, 1, 5, 8, 9};
// const int INPUT_LEN = 5;
// const int INPUT = 9;

int length = 0;

typedef struct list
{
  int val;
  struct list *next;
  struct list *prev;
} list;

// void push(list **l, int val)
// {
//   list *n = calloc(1, sizeof(list));
//   n->next = *l;
//   n->prev = (*l)->prev;

//   (*l)->prev = n;
//   n->val = val;
//   *l = n;
// }

// returns pointer to the new element
list *insert_after(list *l, int val)
{
  list *n = calloc(1, sizeof(list));
  n->val = val;
  n->next = l->next;
  l->next = n;

  n->next->prev = n;
  n->prev = l;
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
    ++length;
  }
  *rightmost = insert_after(*rightmost, unit);
  ++length;
}

int list_length(list *l, int acc)
{
  int len = 1;
  for (list *it = l->next; it != l; it = it->next)
  {
    ++len;
  }
  return len;
}

void print_all(int generation, list *leftmost, list *elf1, list *elf2)
{
  list *it = leftmost;
  printf("%4d (%4d, %4d): ", generation, list_length(leftmost, 0), length);
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
  // printf("init\n");

  list *elf1, *elf2;

  elf1 = leftmost;
  elf1->next = elf1; // circle
  elf1->prev = elf1; // circle

  elf2 = insert_after(elf1, 7);
  list *rightmost = elf2;
  length = 2;

  int generation = 1;
  // int max = 10000000;
  while (!stop(rightmost) && !stop(rightmost->prev) ) //&& generation < max )
  {
    // print_all(generation, leftmost, elf1, elf2);
    ++generation;

    int to_add = elf1->val + elf2->val;
    add_score(&rightmost, to_add);
    elf1 = steps(elf1, 1 + elf1->val);
    elf2 = steps(elf2, 1 + elf2->val);
  }
  // print_all(generation, leftmost, elf1, elf2);
  if (stop(rightmost))
  {
    printf("%d\n", length - INPUT_LEN);
  }
  else if (stop(rightmost->prev))
  {
    printf("previous matched: %d\n", length - INPUT_LEN - 1);
  } else {
    printf("reached limit\n");
  }
  printf("generations: %d\n", generation);
  // print_all(generation, leftmost, elf1, elf2);

  // list *result = steps(leftmost, INPUT);
  // for (int i = 0; i < 10; ++i)
  // {
  //   printf("%d", result->val);
  //   result = result->next;
  // }
  // printf("\n");

  return 0;
}