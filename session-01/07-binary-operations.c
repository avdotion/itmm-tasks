// TASK: Bitwise operations
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>

int getBinary(unsigned int n) {
  if (n) {
    return n % 2 + 10 * getBinary(n / 2);
  } else {
    return 0;
  }
}

unsigned char shift_bitwise_left(unsigned char num, int shift) {
  return (num << shift) | (num >> ((sizeof(char) * 8) - shift));
}

unsigned char shift_bitwise_right(unsigned char num, int shift) {
  return (num >> shift) | (num << ((sizeof(char) * 8) - shift));
}

int main() {
  char buffer[50];
  char *ptr;

  unsigned char x;
  printf("Enter valid decimal integer: ");

  scanf("%s", buffer);
  x = (unsigned char)strtoul(buffer, &ptr, 10);

  char direction;
  printf("Enter shift direction (</>): ");
  scanf(" %c", &direction);

  int shift;
  printf("Enter shift value: ");
  scanf("%s", buffer);
  shift = (int)strtol(buffer, &ptr, 10);

  if (direction == '<' || direction == '>') {
    printf("Given number (decimal): %u\n", x);
    printf("Given number (binary): %d\n", getBinary(x));
    if (direction == '<') {
      printf("Shifted number (decimal): %u\n", shift_bitwise_left(x, shift));
      printf("Shifted number (binary): %d\n", getBinary(shift_bitwise_left(x, shift)));
    } else {
      printf("Shifted number (decimal): %u\n", shift_bitwise_right(x, shift));
      printf("Shifted number (binary): %d\n", getBinary(shift_bitwise_right(x, shift)));
    }
  } else {
    printf("Something went wrong\n");
  }

}
