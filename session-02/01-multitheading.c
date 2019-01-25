/*
Input Example:
  Number of 'Ready' tasks:
  Task 1 CPU-burst:
  ...
  Task N CPU-burst:
  Task 1 processors number:
  ...
  Task N processors number:
  Maximun available processors in PC:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

int main() {
  printf("Number of 'Ready' tasks: ");
  int ready_tasks = get_int();

  int** tasks = malloc(ready_tasks * sizeof(int*));
  for (int task_index = 0; task_index < ready_tasks; ++task_index) {
    /*
      The 'tasks' basic structure:
      [
        [CPU-burst #1, processors-number #1],
        [CPU-burst #2, processors-number #2],
        ...
        [CPU-burst #ready_tasks, processors-number #ready_tasks],
      ]
    */
    tasks[task_index] = malloc(2 * sizeof(int));

    printf("Task %d CPU-burst: ", task_index);
    tasks[task_index][0] = get_int();

    printf("Task %d processors number: ", task_index);
    tasks[task_index][1] = get_int();
  }

  printf("How many processors is available for the tasks? ");
  int available_processors = get_int();

  // Time to choose algorithm!

  printf("Choose one of the algorithms ('fcfs' (default) or 'sjf'): ");
  char algorithm[20];
  scanf("%s", algorithm);

  if (strcmp(algorithm, "sjf")) {
    // sjf
    printf("The 'sjf' has been launched...\n");


  } else {
    // fcfs
    printf("The 'fcfs' has been launched...\n");
  }


  // Debug
  for (int task_index = 0; task_index < ready_tasks; ++task_index) {
    printf("%d/%d\n", tasks[task_index][0], tasks[task_index][1]);
  }
}
