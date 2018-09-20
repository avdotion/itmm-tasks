// TASK: Knapsack problem
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <inttypes.h>

typedef uint32_t bitmask;

int items_number;
double knapsack_capacity;
double items_weights[sizeof(bitmask)];
double items_values[sizeof(bitmask)];
bitmask best_solution = 0;

void printBits(size_t const size, void const * const ptr) {
  unsigned char *b = (unsigned char*) ptr;
  unsigned char byte;

  for (int i = size-1; i >= 0; i--) {
    for (int j = 7; j >= 0; j--) {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    }
  }
  printf("\n");
}

void printArray(size_t const size, double a[]) {
  for (int i = 0; i < size; ++i) {
    printf("%lf, ", a[i]);
  }
  printf("\n");
}

int get_by_index(bitmask b, int index) {
  for (int i = 0; i < index; ++i) {
    b = b >> 1;
  }
  return b % 2;
}

double get_weight(bitmask k) {
  double capacity = 0;
  for (int i = 0; i < items_number; ++i) {
    if (get_by_index(k, i)) {
      capacity += items_weights[i];
    }
  }
  return capacity;
}

double get_value(bitmask k) {
  double value = 0;
  for (int i = 0; i < items_number; ++i) {
    if (get_by_index(k, i)) {
      value += items_values[i];
    }
  }
  return value;
}

void solve_knapsack_problem(int step, bitmask knapsack) {
  if (step < items_number) {
    solve_knapsack_problem(step + 1, (knapsack << 1) + 0);
    solve_knapsack_problem(step + 1, (knapsack << 1) + 1);
  } else if (get_weight(knapsack) <= knapsack_capacity &&
             get_value(knapsack) >= get_value(best_solution)) {
        best_solution = knapsack;
  }
}

int main() {
  /*
  printf("Enter number of items (max %d): ", 2 << sizeof(bitmask));
  scanf("%d", &items_number);

  printf("Enter knapsack set of items in folowing format: weight/value\n");
  for (int i = 0; i < items_number; ++i) {
    printf("items[%d] = ", i);
    scanf("%lf/%lf", &items_weights[i], &items_values[i]);
  }

  printf("Enter knapsack capacity: ");
  scanf("%lf", &knapsack_capacity);
  */
  items_number = 4;
  items_weights[0] = 2.0;
  items_weights[1] = 4.0;
  items_weights[2] = 1.0;
  items_weights[3] = 2.0;
  items_values[0] = 7.0;
  items_values[1] = 2.0;
  items_values[2] = 5.0;
  items_values[3] = 1.0;

  knapsack_capacity = 6.0;
  bitmask knapsack = 0;

  solve_knapsack_problem(0, knapsack);
  printf("%lf\n", get_value(best_solution));
  // printBits(sizeof(best_solution), &best_solution);

  return 0;
}
