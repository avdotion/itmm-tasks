#include <stdio.h>

int main() {
  double numbers[20];
  signed int numbers_amount;

  printf("Enter amount of the real numbers: ");
  scanf("%u", &numbers_amount);
  for (int i = 0; i < numbers_amount; ++i) {
    printf("Enter numbers[%d]: ", i);
    scanf("%lf", &numbers[i]);
  }

  for (int i = 0; i < numbers_amount; ++i) {
    printf("%d: %.2f\n", i, numbers[i]);
  }

  printf("\n");
  for (int i = 0; i < 40; ++i) {
    printf("-");
  }
  printf("\n");

  long double numbers_sum = 0;
  for (int i = 0; i < numbers_amount; ++i) {
    numbers_sum += numbers[i];
  }

  printf("Sum of the numbers: %llf", numbers_sum);
  return 0;
}
