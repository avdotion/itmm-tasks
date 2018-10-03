// TASK: Real numbers I/O
// STATUS: DONE
// MARK: PASSED

#include <stdio.h>
#include <stdlib.h>
#define ROWS 4

int get_length(int a) {
  int length = 0;
  if (a < 0) {
    length++;
    a *= -1;
  }
  while (a > 0) {
    length++;
    a = a / 10;
  }
  return length;
}

int main() {
  int numbers_count;

  char buffer[20];
  char *ptr;

  int max_int_width = 0;

  printf("Enter count of the real numbers: ");
  scanf("%s", buffer);
  numbers_count = (int)strtol(buffer, &ptr, 10);

  double *numbers = malloc(sizeof(double) * numbers_count);

  for (int i = 0; i < numbers_count; ++i) {
    printf("Numbers[%d]: ", i + 1);
    scanf("%s", buffer);
    double n = strtod(buffer, &ptr);
    if (get_length((int)n) > max_int_width) {
      max_int_width = get_length((int)n);
    }
    numbers[i] = ((double)(int)(n * 100)) / 100;
  }

  for (int i = 0; i < numbers_count; ++i) {
    printf("%4d: %*.2f", i+1, max_int_width+3, numbers[i]);
    if (i % ROWS == ROWS - 1) {
      printf("\n");
    }
  }

  printf("\n");

  for (int i = 0; i < numbers_count; ++i) {
    printf("%*.2f\n", max_int_width+3, numbers[i]);
  }

  for (int i = 0; i < 40; ++i) {
    printf("-");
  }

  printf("\n");

  long double numbers_sum = 0;
  for (int i = 0; i < numbers_count; ++i) {
    numbers_sum += numbers[i];
  }

  printf("%.2Lf\n", numbers_sum);
  return 0;
}
