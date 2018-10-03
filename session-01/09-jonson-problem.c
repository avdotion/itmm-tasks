// TASK: Johnson problem
// STATUS: DONE
// MARK: PASSED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int ROWS;
int COLS;

int **matrix;

void print_array(int a[], int size) {
  if (size) {
    printf("array(");
    for (int i = 0; i < size - 1; ++i) {
      printf("%d, ", a[i]);
    }
    printf("%d)\n", a[size-1]);
  } else {
    printf("array()\n");
  }
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int main() {
  char buffer[10];
  char *ptr;

  printf("How many details do you have?\n");
  scanf("%s", buffer);
  ROWS = (int)strtol(buffer, &ptr, 10);

  int **matrix = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; i++) {
    matrix[i] = (int *)malloc(COLS * sizeof(int));
  }

  printf("Enter your matrix in following format: _ _\n");
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      scanf("%s", buffer);
      matrix[i][j] = (int)strtol(buffer, &ptr, 10);
    }
  }

  bool in_matrix[ROWS];
  for (int i = 0; i < ROWS; ++i) {
    in_matrix[i] = true;
  }

  int solution[ROWS];
  int *lower_bound, *upper_bound;
  lower_bound = solution;
  upper_bound = solution + ROWS - 1;

  while (1) {
    // Find minimum
    int minimum_index = -1;
    int minimum_value = 0;
    for (int i = 0; i < ROWS; ++i) {
      if (in_matrix[i]) {
        for (int j = 0; j < COLS; ++j) {
          if (minimum_index == -1 || minimum_value > matrix[i][j]) {
            minimum_index = i;
            minimum_value = matrix[i][j];
          }
        }
      }
    }

    if (minimum_index == -1) {
      break;
    } else if (matrix[minimum_index][0] <= matrix[minimum_index][1]) {
      *lower_bound = minimum_index + 1;
      lower_bound++;
    } else {
      *upper_bound = minimum_index + 1;
      upper_bound--;
    }
    in_matrix[minimum_index] = false;
  }

  print_array(solution, ROWS);

  char first_machine_element[2];
  char first_machine_graph[200] = {'\0'};
  char second_machine_element[2];
  char second_machine_graph[200] = {'\0'};

  int first_machine_index = 0;
  int second_machine_index = 0;

  int s_index = 0;
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < matrix[solution[s_index]-1][0]; ++j) {
      sprintf(first_machine_element, "%d", solution[s_index]);
      strcat(first_machine_graph, first_machine_element);
      first_machine_index++;
    }

    while (second_machine_index < first_machine_index) {
      sprintf(second_machine_element, " ");
      strcat(second_machine_graph, second_machine_element);
      second_machine_index++;
    }

    for (int j = 0; j < matrix[solution[s_index]-1][1]; ++j) {
      sprintf(second_machine_element, "%d", solution[s_index]);
      strcat(second_machine_graph, second_machine_element);
      second_machine_index++;
    }

    s_index++;
  }

  printf("Machine 1: %s\n", first_machine_graph);
  printf("Machine 2: %s\n", second_machine_graph);
  printf("Time spent: %d\n", max((int)strlen(first_machine_graph), (int)strlen(second_machine_graph)));
}
