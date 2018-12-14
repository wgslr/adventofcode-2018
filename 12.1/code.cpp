#include <cstdio>
#include <cstdlib>

char parse(char pattern[])
{
  unsigned char result = 0;
  for (int i = 0; pattern[i] != '\0'; ++i)
  {
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

int main()
{
  char pattern[] = ".#.##";
  print_hex(parse(pattern));
  printf("\n");
  print_bit(parse(pattern), '1', '0');
  return 0;
}