// TASK: Knapsack problem
// STATUS: DONE
// MARK: CALLED-DOWN AGAIN

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

typedef uint32_t bitmask;

int items_number;
double knapsack_capacity;
double items_weights[sizeof(bitmask)];
double items_values[sizeof(bitmask)];

int get_by_index(bitmask b, int index) {
  return (b >> index) % 2;
}

double get_weight(const bitmask *k) {
  double capacity = 0;
  for (int i = 0; i < items_number; ++i) {
    if (get_by_index(*k, i)) {
      capacity += items_weights[i];
    }
  }
  return capacity;
}

double get_value(const bitmask *k) {
  double value = 0;
  for (int i = 0; i < items_number; ++i) {
    if (get_by_index(*k, i)) {
      value += items_values[i];
    }
  }
  return value;
}

int main() {
  char buffer[20];
  char *ptr;

  printf("Enter number of items: ");
  scanf("%s", buffer);
  items_number = (int)strtol(buffer, &ptr, 10);

  printf("Enter weights in a single line: ");
  for (int i = 0; i < items_number; ++i) {
    scanf("%s", buffer);
    items_weights[i] = (double)strtod(buffer, &ptr);
  }

  printf("Enter values in a single line: ");
  for (int i = 0; i < items_number; ++i) {
    scanf("%s", buffer);
    items_values[i] = (double)strtod(buffer, &ptr);
  }

  printf("Enter knapsack capacity: ");
  scanf("%s", buffer);
  knapsack_capacity = strtod(buffer, &ptr);

  bitmask best_solution = 0;

  for (bitmask knapsack = 0; knapsack < (int)(pow(2, items_number)); ++knapsack) {
    if (get_weight(&knapsack) <= knapsack_capacity && get_value(&knapsack) >= get_value(&best_solution)) {
      best_solution = knapsack;
    }
  }

  printf("Solution is %lf\n", get_value(&best_solution));
  printf("You may take:\n");
  for (int i = 0; i < items_number; ++i) {
    if (get_by_index(best_solution, i)) {
      printf("item #%d (w = %.2f, c = %.2f)\n", i+1, items_weights[i], items_values[i]);
    }
  }
  
  return 0;
}
