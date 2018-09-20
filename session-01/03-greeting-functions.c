#include <stdio.h>
#include <stdbool.h>

bool is_prime(long long int number) {
  unsigned long long int d = 2;
  while (number % d != 0 && d * d <= number) {
    ++d;
  }
  return d * d > number;
}

int main() {
  unsigned long long int n;
  scanf("%llu", &n);
  if (n % 2 == 0) {
    for (unsigned long long int i = 2; i <= n / 2; ++i) {
      if (is_prime(i) && is_prime(n - i)) {
        printf("(%llu, %llu); ", i, n - i);
      }
    }
    printf("\n");
  } else {
    printf("Wrong given data\n");
  }
  return 0;
}
