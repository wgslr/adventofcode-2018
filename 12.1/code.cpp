#include <cstdio>
#include <cstdlib>
#include <cstring>

const int SIZE = 200;
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

  printf("switch(%s)\n{\n");

  while (scanf("%s => %c", pattern, &result) != EOF)
  {
    if (result == '#')
    {
      unsigned char binary = parse(pattern);
      printf("  case 0x%X:  \n    return 1;\n", binary);
    }
  }
  printf("  default:\n    return 0;\n}");
}

inline unsigned char next(unsigned char current)
{
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

int main(int argc, char *argv[])
{
  if (argc > 1 && strcmp(argv[1], "generate") == 0)
  {
    generate_classifier();
    return 0;
  }

  state[0] = (unsigned char *)calloc(SIZE, sizeof(unsigned char));
  state[1] = (unsigned char *)calloc(SIZE, sizeof(unsigned char));

  // unsigned char test[2] = {0x01, 0xC0};
  // printf("%x %x\n", test[0], test[1]);
  // printf("%u\n", *((short *)test));
  // printf("%u\n", (*((short *)test)) << 1);
  // printf("%u\n\n", sizeof(short));

  // print_bit(0xF0, '1', '0');
  // printf("\n");
  // print_bit(0xF0 << -1, '1', '0');
  // printf("\n");
  // print_bit(0xFF >> 1, '1', '0');
  // printf("\n");

  // ("%x %x\n", 0xF00F, 0xF00F << -1);

  read_input();
  for (int i = 0; i < SIZE; ++i)
  {
    print_pots(state[0][i]);
    printf(" ");
  }

  printf("\n\n");
  for (int i = first; i <= last; ++i)
  {
    print_pots(get5(state[0], i));
    printf("\n");
  }

  printf("First %u last %u\n", first, last);

  printf("%d\n", score(state[0]));

  return 0;
}