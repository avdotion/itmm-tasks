// TASK: Function greeting
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Primality test
bool is_prime(long long int n) {
  if (n % 2 == 0) {
    return n == 2;
  }
  unsigned long long int d = 3;
  while (n % d != 0 && d * d <= n) {
    d += 2;
  }
  return d * d > n;
}

int main() {
  printf("Enter even N (N > 2): ");
  char buffer[10];
  char *ptr;

  unsigned long long int n;
  scanf("%s", buffer);
  n = strtoull(buffer, &ptr, 10);
  if (n > 2 && n % 2 == 0) {
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
