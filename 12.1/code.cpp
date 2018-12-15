#include <cstdio>
#include <cstdlib>
#include <cstring>

const int SIZE = 2000;
unsigned char *state[2];

// counting bits
const int ZERO = SIZE * 8 / 2; // ofset
int first = ZERO;
int last = ZERO;

char parse(char pattern[])
{
  unsigned char result = 0;
  for (int i = 0; pattern[i] != '\0'; ++i)
  {
    // result |= (pattern[i] == '#' ? 0x01 : 0x00) << (8 - i - 1);
    result <<= 1;
    result |= pattern[i] == '#' ? 0x01 : 0x00;
  }
  return result;
}

void print_hex(const unsigned char octet)
{
  printf("%X%X", octet >> 4, octet & 0x0F);
}

void print_bit(const unsigned char octet, char char1, char char0)
{
  for (unsigned char mask = 1 << 7; mask > 0; mask >>= 1)
  {
    printf("%c", octet & mask ? char1 : char0);
  }
}

void print_pots(const unsigned char octet)
{
  print_bit(octet, '#', '.');
}

void generate_classifier()
{
  char pattern[8];
  char result;

  printf("switch(%s)\n{\n", "current");

  while (scanf("%s => %c", pattern, &result) != EOF)
  {
    if (result == '#')
    {
      unsigned char binary = parse(pattern);
      // printf("  case 0x%X:  \n    return 1;\n", binary);
      printf("  case 0b");
      print_bit(binary, '1', '0');
      printf(":\n    return 1;\n");
    }
  }
  printf("  default:\n    return 0;\n}");
}

inline unsigned char next(unsigned char current)
{
#ifndef TEST
  switch (current)
  {
  case 0xB:
    return 1;
  case 0xA:
    return 1;
  case 0x5:
    return 1;
  case 0x1A:
    return 1;
  case 0x18:
    return 1;
  case 0x7:
    return 1;
  case 0xC:
    return 1;
  case 0x4:
    return 1;
  case 0xD:
    return 1;
  case 0x1E:
    return 1;
  case 0x11:
    return 1;
  case 0x1D:
    return 1;
  case 0x2:
    return 1;
  case 0x9:
    return 1;
  case 0x16:
    return 1;
  default:
    return 0;
  }

#else 
  switch (current)
  {
  case 0b00000011:
    return 1;
  case 0b00000100:
    return 1;
  case 0b00001000:
    return 1;
  case 0b00001010:
    return 1;
  case 0b00001011:
    return 1;
  case 0b00001100:
    return 1;
  case 0b00001111:
    return 1;
  case 0b00010101:
    return 1;
  case 0b00010111:
    return 1;
  case 0b00011010:
    return 1;
  case 0b00011011:
    return 1;
  case 0b00011100:
    return 1;
  case 0b00011101:
    return 1;
  case 0b00011110:
    return 1;
  default:
    return 0;
  }
#endif
}

inline void set(unsigned char *st, bool val, int pos)
{
  const int octet = pos / 8;
  const int bit = pos % 8;
  if (val)
  {
    st[octet] |= val << (7 - bit);
  }
  else
  {
    st[octet] &= ~(1 << (7 - bit));
  }
}

void read_input()
{
  char buff[200];
  scanf("initial state: %s", buff);

  for (int i = 0; buff[i] != '\0'; ++i)
  {
    set(state[0], buff[i] == '#', ZERO + i);
    if ('#' == buff[i])
      last = ZERO + i;
  }
}

bool get1(const unsigned char *const st, int pos)
{
  const int octet = pos / 8;
  const int bit = pos % 8;

  return !!(st[octet] & (0x01 << (7 - bit)));
}

// gets the sourroundings of given pos
inline unsigned char get5(const unsigned char *const st, const int pos)
{
  const int first = pos - 2;
  const int octet = first / 8;
  const int bit = first % 8;
  if (bit <= 3)
  { // contained in one octet
    // clean irrelevant bits to the left and then move to the rightmost bits
    return (st[octet] & (0xFF >> bit)) >> (3 - bit);
  }
  else
  {
    const unsigned overflow = bit - 3;
    const unsigned char result = (st[octet] & (0xFF >> bit)) << overflow;
    return result | st[octet + 1] >> (8 - overflow);
  }
}

int score(const unsigned char *const st)
{
  int result = 0;
  for (int i = first; i < last; ++i)
  {
    if (get1(st, i))
    {
      result += i - ZERO;
    }
  }
  return result;
}

void print_all(const unsigned char *const st)
{
  printf("(%d:%d) ", first, last);
  for (int i = first / 8; i <= last / 8; ++i)
  {
    print_pots(st[i]);
    printf(" ");
  }
  printf("\n");
}

int main(int argc, char *argv[])
{
  if (argc > 1 && strcmp(argv[1], "generate") == 0)
  {
    generate_classifier();
    return 0;
  }

  const int generations = atoi(argv[1]);

  state[0] = (unsigned char *)calloc(SIZE, sizeof(unsigned char));
  state[1] = (unsigned char *)calloc(SIZE, sizeof(unsigned char));

  read_input();

  int curr, prev;
  prev = 0;
  curr = 1;

  int i = 0;
  for (; i < generations; ++i)
  {
    last += 2; // heurisitic
    first -= 2;
    for (int i = first; i <= last; ++i)
    {
      set(state[curr], next(get5(state[prev], i)), i);
    }

    print_all(state[curr]);
    prev = curr;
    curr = !prev;

    if (i % 10000 == 0)
    {
      fprintf(stderr, "generation %d\tfirst %d\tlast %d=%d\n", i, first, last, last / 8);
    }
  }
  fprintf(stderr, "generation %d\tfirst %d\tlast %d=%d\n", i, first, last, last / 8);

  printf("%d\n", score(state[0]));

  return 0;
}