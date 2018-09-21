// TASK: Function greeting
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Primality test
bool is_prime(long long int number) {
  unsigned long long int d = 2;
  while (number % d != 0 && d * d <= number) {
    ++d;
  }
  return d * d > number;
}

int main() {
  printf("Enter even N (N > 2): ");
  char buffer[50];
  char *ptr;

  unsigned long long int n;
  scanf("%s", buffer);
  n = strtoull(buffer, &ptr, 10);
  if (n % 2 == 0) {
    for (unsigned long long int i = 2; i <= n / 2; ++i) {
      if (is_prime(i) && is_prime(n - i)) {
        printf("(%llu, %llu), ", i, n - i);
      }
    }
    printf("\n");
  } else {
    printf("Oops, something went wrong...\n");
  }
  return 0;
}
