// TASK: Real numbers I/O
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>

int main() {
  int numbers_count;

  char buffer[50];
  char *ptr;

  printf("Enter count of the real numbers: ");
  scanf("%s", buffer);
  numbers_count = (int)strtol(buffer, &ptr, 10);

  double *numbers = malloc(sizeof(double) * numbers_count);

  for (int i = 0; i < numbers_count; ++i) {
    printf("Enter numbers[%d]: ", i + 1);
    scanf("%s", buffer);
    numbers[i] = strtod(buffer, &ptr);
  }

  for (int i = 0; i < numbers_count; ++i) {
    printf("%d: %.2f\n", i+1, numbers[i]);
  }

  printf("\n");

  for (int i = 0; i < 40; ++i) {
    printf("-");
  }

  printf("\n");

  long double numbers_sum = 0;
  for (int i = 0; i < numbers_count; ++i) {
    numbers_sum += numbers[i];
  }

  printf("Sum of the numbers: %Lf", numbers_sum);
  return 0;
}
