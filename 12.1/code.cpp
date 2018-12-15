#include <cstdio>
#include <cstdlib>
#include <cstring>

const int SIZE = 200;
const int ZERO = SIZE * 8 / 2; // ofset
unsigned char *state[2];

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

void set(unsigned char*  st , bool val, int pos)
{
  printf("Set %d to %d\n", pos, val);
  const int octet = pos >> 3;
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
    set(state[0], buff[i] == '#', ZERO + i );
  }
}

int main(int argc, char *argv[])
{
  if (argc > 1 && strcmp(argv[1], "generate") == 0)
  {
    generate_classifier();
    return 0;
  }

  state[0] = (unsigned char*)calloc(SIZE, sizeof(unsigned char));
  state[1] = (unsigned char*)calloc(SIZE, sizeof(unsigned char));

  read_input();
  for (int i = 0; i < SIZE; ++i)
  {
    print_pots(state[0][i]);
    printf(" ");
  }

  return 0;
}