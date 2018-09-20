#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ROWS;
int COLS = 2;

typedef struct {
  int *data;
  size_t size;
  size_t _reserved_size;
} stack;

void initStack(stack *a, size_t initial_size) {
  a->data = (int *)malloc(initial_size * sizeof(int));
  a->size = 0;
  a->_reserved_size = initial_size;
}

void pushStack(stack *a, int item) {
  if (a->size == a->_reserved_size) {
    a->_reserved_size *= 2;
    a->data = (int *)realloc(a->data, a->_reserved_size * sizeof(int));
  }
  a->data[a->size++] = item;
}

int popStack(stack *a) {
  if (a->size) {
    if (a->_reserved_size / 2 > a->size) {
      a->_reserved_size /= 2;
      a->data = (int *)realloc(a->data, a->_reserved_size * sizeof(int));
    }
    int item = a->data[a->size - 1];
    a->size--;
    return item;
  }
  return 0;
}

void printStack(stack *a) {
  if (a->size) {
    printf("stack(");
    for (int i = 0; i < a->size - 1; ++i) {
      printf("%d, ", a->data[i]);
    }
    printf("%d)\n", a->data[a->size-1]);
  } else {
    printf("stack()\n");
  }
}

void printArray(int a[], int size) {
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

typedef struct {
  int i;
  int j;
} pair;

pair minMatrix(int **array) {
  pair minimum;
  minimum.i = 0;
  minimum.j = 0;

  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      if (array[i][j] < array[minimum.i][minimum.j]) {
        minimum.i = i;
        minimum.j = j;
      }
    }
  }
  return minimum;
}

void printPair(pair p) {
  printf("(%d, %d)\n", p.i, p.j);
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

void copyArray(int (*dest)[ROWS][COLS], int (*values)[ROWS][COLS]) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      *dest[i][j] = *values[i][j];
    }
  }
}

int main() {
  FILE *fopen(), *fin;
  fin = fopen("10-johnson-problem-test.txt", "r");
  if (!fin) {
    printf("Error reading file!\n");
    return EXIT_FAILURE;
  }

  fscanf(fin, "%d\n", &ROWS);
  printf("%d\n", ROWS);

  int element;
  int **matrix = (int **)malloc(ROWS * sizeof(int *));
  for (int i = 0; i < ROWS; i++) {
    matrix[i] = (int *)malloc(COLS * sizeof(int));
  }

  int index = 0;

  for (int i = 0; i < ROWS; ++i) {
    fscanf(fin, "%d", &element);
    matrix[i][0] = element;
  }

  for (int i = 0; i < ROWS; ++i) {
    fscanf(fin, "%d", &element);
    matrix[i][1] = element;
  }

  // Copy data from given array to "copied"
  int matrix_copied[ROWS][COLS];
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      matrix_copied[i][j] = matrix[i][j];
    }
  }

  // The Johnson problem algorithm
  stack first_machine;
  initStack(&first_machine, 1);
  stack second_machine;
  initStack(&second_machine, 1);

  while (1) {
    pair minimum = minMatrix(matrix);
    if (matrix[minimum.i][minimum.j] == 1337) {
      break;
    } else if (minimum.j == 0) {
      pushStack(&first_machine, minimum.i + 1);
      matrix[minimum.i][0] = 1337;
      matrix[minimum.i][1] = 1337;
    } else if (minimum.j == 1) {
      pushStack(&second_machine, minimum.i + 1);
      matrix[minimum.i][0] = 1337;
      matrix[minimum.i][1] = 1337;
    }
  }

  // Reverse the first stack
  stack first_machine_reversed;
  initStack(&first_machine_reversed, 1);

  while (first_machine.size != 0) {
    pushStack(&first_machine_reversed, popStack(&first_machine));
  }

  // P - maybe from "Process"?
  // Print solution in given form
  int P[ROWS];
  int P_index = 0;
  while (first_machine_reversed.size != 0) {
    P[P_index++] = popStack(&first_machine_reversed);
  }

  while (second_machine.size != 0) {
    P[P_index++] = popStack(&second_machine);
  }

  printArray(P, ROWS);

  char first_machine_element[2];
  char first_machine_graph[200] = {'\0'};
  char second_machine_element[2];
  char second_machine_graph[200] = {'\0'};

  int first_machine_index = 0;
  int second_machine_index = 0;

  P_index = 0;
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < matrix_copied[P[P_index]-1][0]; ++j) {
      sprintf(first_machine_element, "%d", P[P_index]);
      strcat(first_machine_graph, first_machine_element);
      first_machine_index++;
    }

    while (second_machine_index < first_machine_index) {
      sprintf(second_machine_element, " ");
      strcat(second_machine_graph, second_machine_element);
      second_machine_index++;
    }

    for (int j = 0; j < matrix_copied[P[P_index]-1][1]; ++j) {
      sprintf(second_machine_element, "%d", P[P_index]);
      strcat(second_machine_graph, second_machine_element);
      second_machine_index++;
    }

    P_index++;
  }

  printf("Machine 1: %s\n", first_machine_graph);
  printf("Machine 2: %s\n", second_machine_graph);
  printf("Time spent: %d\n", max(strlen(first_machine_graph), strlen(second_machine_graph)));
}
