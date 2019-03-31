// TASK: Scheduler in a uniprocessor OS
// STATUS: NOT PASSED YET
// MARK: ON HOLD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LOWER_BOUND_EXECUTION_TIME 10
#define UPPER_BOUND_EXECUTION_TIME 50
#define UPPER_BOUND_TOTAL_TASKS 30
#define TASKS_LIMIT_TO_PRINT_TO_A_FILE 21

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

int get_random_int(int lower_bound, int upper_bound) {
  return rand() % (upper_bound - lower_bound) + lower_bound;
}

typedef struct Task {
  int execution_time;
  bool was_launched;
} Task;

int get_quantum(int total_tasks, Task* tasks) {
  // mean by execution time
  // int sum = 0;
  // for (int task_index = 0; task_index < total_tasks; ++task_index) {
  //   if (!(tasks[task_index]).was_launched) {
  //     sum += (tasks[task_index]).execution_time;
  //   }
  // }
  // return (double) sum / (double)total_tasks * 2;
  return get_random_int(
    LOWER_BOUND_EXECUTION_TIME + 10,
    UPPER_BOUND_EXECUTION_TIME + 10
  );
}

int main() {
  // https://stackoverflow.com/a/822368
  srand(time(NULL));
  printf("Choose an index of the related input option:\n");
  printf("1) Read data from a keyboard\n");
  printf("2) Random data\n");
  printf("3) Read from a file\n");
  printf("Make sure that a task execution time belongs to the segment [%d, %d]!\n",
    LOWER_BOUND_EXECUTION_TIME,
    UPPER_BOUND_EXECUTION_TIME
  );
  printf("Your choice is ");
  int input_type = get_int();

  int total_tasks = 0;
  Task* tasks;
  if (input_type == 1) {
    printf("How many tasks do you want to lauch? ");
    total_tasks = get_int();
    if (!(0 < total_tasks && total_tasks <= UPPER_BOUND_TOTAL_TASKS)) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }

    tasks = malloc(total_tasks * sizeof *tasks);
    for (int task_index = 0; task_index < total_tasks; ++task_index) {

      printf("Enter the %d task execution time: ", task_index + 1);
      tasks[task_index].execution_time = get_int();

      if (!(LOWER_BOUND_EXECUTION_TIME <= tasks[task_index].execution_time &&
            tasks[task_index].execution_time <= UPPER_BOUND_EXECUTION_TIME)) {
        // Exception handling
        printf("An error occurred!\n");
        return (EXIT_FAILURE);
      }
    }
  } else if (input_type == 2) {
    total_tasks = get_random_int(1, UPPER_BOUND_TOTAL_TASKS);
    tasks = malloc(total_tasks * sizeof *tasks);
    for (int task_index = 0; task_index < total_tasks; ++task_index) {
      tasks[task_index].execution_time = get_random_int(
        LOWER_BOUND_EXECUTION_TIME,
        UPPER_BOUND_EXECUTION_TIME
      );
    }
  } else if (input_type == 3) {
    FILE *fp;
    fp = fopen("input.txt", "r");

    char buffer[20];
    char *ptr;

    fscanf(fp, "%s", buffer);
    total_tasks = (int)strtol(buffer, &ptr, 10);

    tasks = malloc(total_tasks * sizeof *tasks);
    for (int task_index = 0; task_index < total_tasks; ++task_index) {
      fscanf(fp, "%s", buffer);
      tasks[task_index].execution_time = (int)strtol(buffer, &ptr, 10);
    }
  } else {
    // Exception handling
    printf("An error occurred!\n");
    return (EXIT_FAILURE);
  }

  // The only way I found to avoid a hardcode
  char chest[94*100];
  int chest_p = sprintf(chest, "");

  // To prevent Linux <<-operator mess
  printf("\n");

  chest_p += sprintf(chest + chest_p, "*---------+----------------+\n");
  chest_p += sprintf(chest + chest_p, "|    N    | Execution time |\n");
  chest_p += sprintf(chest + chest_p, "*---------+----------------+\n");
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    chest_p += sprintf(chest + chest_p, "| %7d | %14d |\n",
      task_index + 1,
      tasks[task_index].execution_time
    );
  }
  chest_p += sprintf(chest + chest_p, "*---------+----------------+\n");

  chest_p += sprintf(chest + chest_p, "\n");
  chest_p += sprintf(chest + chest_p, "+------------+-------------+----------------+-----------+------------------+---------------+\n");
  chest_p += sprintf(chest + chest_p, "| Itteration | CPU Quantum | Summary CPU    | A chosen  | CPU-burst of a   | CPU remaining |\n");
  chest_p += sprintf(chest + chest_p, "|            |             | available time | processor | chosen processor | time          |\n");
  chest_p += sprintf(chest + chest_p, "+------------+-------------+----------------+-----------+------------------+---------------+\n");

  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    // Having the structure is better than
    // is_the_task_was_launched[task_index] = false;
    tasks[task_index].was_launched = false;
  }

  // The "sprintf" procedure could be here
  int result[total_tasks];
  int p_result = 0;

  // The quantums from the example, that may be useful
  // int quantums[7] = {43, 13, 3, 3, 44, 1, 5};

  int cpu_time_remainder = 0;
  // chest_p += sprintf(chest + chest_p, "Debug: { quantum: %d}\n", quantum);

  // The first column formating disallows repeating
  int last_itteration_in_snap = 0;

  for (int itteration = 1; total_tasks - p_result > 0 && itteration < 1000; ++itteration) {
    int quantum = get_quantum(total_tasks, tasks);
    // int quantum = quantums[itteration];
    int cpu_summary_time = quantum + cpu_time_remainder;
    bool is_quantum_used_at_least_once = false;

    while (true) {
      int task_index_lowest_positive_delta = -1;
      int lowest_positive_delta = 3 * UPPER_BOUND_EXECUTION_TIME;
      for (int task_index = 0; task_index < total_tasks; ++task_index) {
        Task current_task = tasks[task_index];
        int delta = cpu_summary_time - current_task.execution_time;
        if (0 <= delta && delta < lowest_positive_delta &&
            !current_task.was_launched) {
          task_index_lowest_positive_delta = task_index;
          lowest_positive_delta = delta;
        }
      }

      if (task_index_lowest_positive_delta == -1) {
        break;
      }

      tasks[task_index_lowest_positive_delta].was_launched = true;
      int remaining_time = lowest_positive_delta;

      char itteration_marker[5];
      if (last_itteration_in_snap == itteration) {
        sprintf(itteration_marker, "%s", "");
      } else {
        sprintf(itteration_marker, "%d", itteration);
      }
      last_itteration_in_snap = itteration;

      chest_p += sprintf(chest + chest_p, "| %10s | %11d | %14d | %9d | %16d | %13d |\n",
        itteration_marker,
        quantum,
        cpu_summary_time,
        task_index_lowest_positive_delta + 1,
        tasks[task_index_lowest_positive_delta].execution_time,
        remaining_time
      );
      result[p_result++] = task_index_lowest_positive_delta;
      is_quantum_used_at_least_once = true;
      cpu_time_remainder = remaining_time;

      if (remaining_time <= 0) {
        // Healthy behavior
        break;
      }
      cpu_summary_time = remaining_time;
    }

    if (!is_quantum_used_at_least_once) {
      // The case when quantum was not enough
      cpu_time_remainder = cpu_summary_time;
      chest_p += sprintf(chest + chest_p, "| %10d | %11d | %14d | %9c | %16c | %13d |\n",
        itteration,
        quantum,
        cpu_summary_time,
        '-',
        '-',
        cpu_time_remainder
      );
    }
  }

  chest_p += sprintf(chest + chest_p, "+------------+-------------+----------------+-----------+------------------+---------------+\n");
  chest_p += sprintf(chest + chest_p, "\n");
  chest_p += sprintf(chest + chest_p, "A possible solution: { ");
  for (int i = 0; i < total_tasks - 1; ++i) {
    chest_p += sprintf(chest + chest_p, "%d, ", result[i] + 1);
  }
  chest_p += sprintf(chest + chest_p, "%d }\n", result[total_tasks - 1] + 1);

  if (total_tasks >= TASKS_LIMIT_TO_PRINT_TO_A_FILE) {
    FILE *fp;
    fp = fopen("output.txt", "w");
    fprintf(fp, "%s", chest);
    fclose(fp);
    printf("The answer had been successfully written to the \"output.txt\"\n");
  } else {
    printf("%s", chest);
  }
  return 0;
}
