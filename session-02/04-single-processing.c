#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

int get_random_int(int min, int max) {
  return rand() % (max - min) + min;
}

typedef struct Task {
  int index;
  int execution_time;
} Task;

int main() {
  // Keyboard input
  printf("How many tasks do you want to lauch? ");
  int total_tasks = get_int();
  if (total_tasks <= 0) {
    // Exception handling
    printf("An error occurred!\n");
    return (EXIT_FAILURE);
  }

  Task* tasks = malloc(total_tasks * sizeof *tasks);
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    tasks[task_index].index = task_index;

    printf("Enter the %d task execution time: ", task_index);
    tasks[task_index].execution_time = get_int();
    if (tasks[task_index].execution_time <= 0) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }
  }

  // Random generation
  int total_tasks = get_random_int(10, 30);
  Task* tasks = malloc(total_tasks * sizeof *tasks);
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    tasks[task_index].index = task_index;
    tasks[task_index].execution_time = get_random_int(1, 50);
  }

  // Reading from a file
  FILE *fp;
  char buff[255];
  fp = fopen("04-test-01.txt", "r");
  fscanf(fp, "%s", buff);
  printf("1 : %s\n", buff );

  // Print all inputed data in the table!


  return 0;
}
