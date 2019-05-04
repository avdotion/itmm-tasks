// TASK: Bitwise operations
// STATUS: DONE
// MARK: PASSED

#include <stdio.h>
#include <stdlib.h>

void print_binary(unsigned char n, int length) {
  if (length > 0) {
    if (n) {
      print_binary(n >> 1, length-1);
      printf("%d", n % 2);
    } else {
      print_binary(0, length-1);
      printf("0");
    }
  }
}

unsigned char shift_bitwise_left(unsigned char num, int shift) {
  return (num << shift) | (num >> ((sizeof(char) * 8) - shift));
}

unsigned char shift_bitwise_right(unsigned char num, int shift) {
  return (num >> shift) | (num << ((sizeof(char) * 8) - shift));
}

int main() {
  char buffer[3];
  char *ptr;

  unsigned char x;
  printf("Enter valid decimal integer [0, 255]: ");

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
    printf("Given number (binary): ");
    print_binary(x, 8);
    printf("\n");
    if (direction == '<') {
      printf("Shifted number (decimal): %u\n", shift_bitwise_left(x, shift));
      printf("Shifted number (binary): ");
      print_binary(shift_bitwise_left(x, shift), 8);
      printf("\n");
    } else {
      printf("Shifted number (decimal): %u\n", shift_bitwise_right(x, shift));
      printf("Shifted number (binary): ");
      print_binary(shift_bitwise_right(x, shift), 8);
      printf("\n");
    }
  } else {
    printf("Something went wrong\n");
  }

}
