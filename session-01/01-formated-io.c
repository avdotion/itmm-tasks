// TASK: Formated I/O
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main() {
  // Assignment
  char symbol;
  int integer_number;
  double real_number;
  char string[100];

  // Using strtol() and strtod() instead of using scanf() for integer
  char buffer[100];
  char *ptr;

  // Input
  printf("Enter a symbol (char): ");
  scanf("%c", &symbol);

  printf("Enter an integer number (int): ");
  scanf("%s", buffer);
  integer_number = (int)strtol(buffer, &ptr, 10);

  printf("Enter an real number (double): ");
  scanf("%s", buffer);
  real_number = strtod(buffer, &ptr);
  getchar();

  printf("Enter a string (char array): ");
  fgets(string, 100, stdin);

  if (string[strlen(string) - 1] == '\n') {
    string[strlen(string) - 1] = '\0';
  }

  // Output
  printf("\n");
  printf("Type \"char\" can act...\n");
  printf("[%c] - like a char\n", symbol);
  printf("[%5c] - like a char with width equals to 5\n", symbol);
  printf("[%-5c] - like a char with width equals to 5 (left-aligned)\n", symbol);
  printf("[%d] - like an decimal integer (symbol-code)\n", symbol);
  printf("[%o] - like an octal integer\n", symbol);
  printf("[%x] - like an hexadecimal integer\n", symbol);
  printf("[%p] - like a pointer address\n", (void *)&symbol);
  printf("\n");
  printf("Type \"int\" can act...\n");
  printf("[%d] - like a decimal integer\n", integer_number);
  printf("[%+d] - like a decimal integer (+ forced)\n", integer_number);
  printf("[%u] - like a decimal unsigned integer\n", integer_number);
  printf("[%o] - like an octal integer\n", integer_number);
  printf("[%x] - like an hexadecimal integer\n", integer_number);
  printf("[%c] - like a char from ASCI\n", integer_number);
  printf("[%p] - like a pointer address\n", (void *)&integer_number);
  printf("\n");
  printf("Type \"double\" can act...\n");
  printf("[%lf] - like a real number (fixed-notation)\n", real_number);
  printf("[%4.2f] - like a real number (fixed-notation 4:2)\n", real_number);
  printf("[%+4.0f] - like a real number (fixed-notation and + forced)\n", real_number);
  printf("[%e] - like a real number (e-notation)\n", real_number);
  printf("[%E] - like a real number (E-notation)\n", real_number);
  printf("[%g] - like a real number (smart notation)\n", real_number);
  printf("[%p] - like a pointer address\n", (void *)&real_number);
  printf("\n");
  printf("Type \"char array\" can act...\n");
  printf("[%s] - like a string\n", string);
  printf("[%p] - like a pointer address\n", (void *)&string);
  return 0;
}
