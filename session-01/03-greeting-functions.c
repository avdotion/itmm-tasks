// TASK: Function greeting
// STATUS: DONE
// MARK: CALL-DOWN

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Primality test
bool is_prime(long long int n) {
  if (n % 2 == 0) {
    return n == 2;
  }
  long long int d = 3;
  while (n % d != 0 && d * d <= n) {
    d += 2;
  }
  return d * d > n;
}

int main() {
  printf("Enter even N (N > 2): ");

  char buffer[10];
  char *ptr;

  bool wrong_input = false;

  unsigned long long int n;
  do {
    if (wrong_input) {
      printf("Oops, something went wrong! Please, try again: ");
    }
    scanf("%s", buffer);
    n = strtoull(buffer, &ptr, 10);
    wrong_input = true;
  } while (!(n > 2 && n % 2 == 0));

  for (long long int i = 2; i <= n / 2; ++i) {
    if (is_prime(i) && is_prime(n - i)) {
      printf("(%llu, %llu), ", i, n - i);
    }
  }
  printf("\n");
  return 0;
}
