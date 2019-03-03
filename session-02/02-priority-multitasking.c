// TASK: Priority Planning Scheduler
// STATUS: NOT PASSED YET
// MARK: ON HOLD

/*
  Usage example:

  processors_limit = 6
  [label] [delay] [CPU-burst] [N] [priority]
   A       1       3           3   2
   B       2       4           2   2
   C       3       2           3   1
   D       0       5           1   2

       1  2  3  4  5  6
    +---------------------processors-->
  0 | [D][             ]
  1 | [A  A  A][D][    ]
  2 | [A  A  A][B  B][D]
  3 | [C  C  C][B  B][D]
  4 | [C  C  C][B  B][D]
  5 | [B  B]
    |
    |
    t
    i
    m
    e
    |
    v
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

typedef struct Task {
  int index;
  // char label;
  int delay;
  int cpu_burst;
  int processors_required;
  int priority;
} Task;

int compare_tasks_cpu_bursts(const void* a, const void* b) {
    Task *left_task = *(Task**)a;
    Task *right_task = *(Task**)b;

    if (left_task->cpu_burst < right_task->cpu_burst)
        return 1;
    else if (left_task->cpu_burst > right_task->cpu_burst)
        return -1;
    else
        return 0;
}

int compare_tasks_delays(const void* a, const void* b) {
    Task *left_task = *(Task**)a;
    Task *right_task = *(Task**)b;

    if (left_task->delay < right_task->delay)
        return -1;
    else if (left_task->delay > right_task->delay)
        return 1;
    else
        return 0;
}

int compare_tasks_processors_required(const void* a, const void* b) {
    Task *left_task = *(Task**)a;
    Task *right_task = *(Task**)b;

    if (left_task->processors_required < right_task->processors_required)
        return -1;
    else if (left_task->processors_required > right_task->processors_required)
        return 1;
    else
        return 0;
}

int compare_tasks_priorities(const void* a, const void* b) {
    Task *left_task = *(Task**)a;
    Task *right_task = *(Task**)b;

    if (left_task->priority < right_task->priority)
        return -1;
    else if (left_task->priority > right_task->priority)
        return 1;
    else
        return 0;
}

int main() {
  printf("How many tasks do you want to lauch? ");
  int total_tasks = get_int();
  if (total_tasks <= 0) {
    // Exception handling
    printf("An error occurred!\n");
    return (EXIT_FAILURE);
  }
  Task* tasks = malloc(total_tasks * sizeof *tasks);

  printf("How many processors are available? ");
  int processors_limit = get_int();
  if (processors_limit <= 0) {
    // Exception handling
    printf("An error occurred!\n");
    return (EXIT_FAILURE);
  }

  printf("Every task must has the following atributes:\n");
  printf("- delay\n- CPU-burst\n- processors\n- priority\n");

  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    tasks[task_index].index = task_index;

    printf("Enter the %d task delay: ", task_index);
    tasks[task_index].delay = get_int();
    if (tasks[task_index].delay < 0) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }

    printf("Enter the %d task CPU-burst: ", task_index);
    tasks[task_index].cpu_burst = get_int();
    if (tasks[task_index].cpu_burst <= 0) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }

    printf("Enter the %d task processors required: ", task_index);
    tasks[task_index].processors_required = get_int();
    if (tasks[task_index].processors_required <= 0) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }

    printf("Enter the %d task priority (1..): ", task_index);
    tasks[task_index].priority = get_int();
    if (tasks[task_index].priority <= 0) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }
  }

  /*
  - Preparing data (sorting)
    - Sort by CPU-burst (>)
    - Sort by delay (<)
    - Sort by processors_required (<)
    - Sort by priority (<)
  */

  Task** p_tasks = (Task **)malloc(total_tasks * sizeof(Task *));
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    p_tasks[task_index] = &tasks[task_index];
  }

  qsort(p_tasks, total_tasks, sizeof(Task*), compare_tasks_cpu_bursts);
  qsort(p_tasks, total_tasks, sizeof(Task*), compare_tasks_delays);
  qsort(p_tasks, total_tasks, sizeof(Task*), compare_tasks_processors_required);
  qsort(p_tasks, total_tasks, sizeof(Task*), compare_tasks_priorities);

  // Printing a prepeared data table
  printf("[label]\t[delay]\t[CPU-b]\t[procs]\t[prior]\n");
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    Task current_task = *(p_tasks[task_index]);
    printf("%c\t%d\t%d\t%d\t%d\n", current_task.index + (int)'A',
                                   current_task.delay,
                                   current_task.cpu_burst,
                                   current_task.processors_required,
                                   current_task.priority);
  }

  int *cpu_bursts = malloc(total_tasks * sizeof(int));
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    Task current_task = *(p_tasks[task_index]);
    cpu_bursts[current_task.index] = current_task.cpu_burst;
  }

  int average_working_time = 0;
  int average_holing_time = 0;
  printf("    +---------------------processors-->\n");
  // t - time on the timeline axis
  for (int t = 0; ; ++t) {
    // Snapshot - a single row in a timeline
    int* snap = malloc(processors_limit * sizeof(int));
    for (int i = 0; i < processors_limit; ++i) {
      snap[i] = -1;
    }
    int snap_p = 0;

    // A task can be launched only once in a row
    bool* tasks_blacklist = malloc(total_tasks * sizeof(int));
    for (int i = 0; i < processors_limit; ++i) {
      tasks_blacklist[i] = false;
    }

    for (int task_index = 0; task_index < total_tasks; ++task_index) {
      Task current_task = *(p_tasks[task_index]);
      // Warning: a miserable thing to use 'task_index' in squared brackets
      if (!tasks_blacklist[current_task.index] &&
          cpu_bursts[current_task.index] > 0 &&
          current_task.delay <= t &&
          processors_limit - snap_p >= current_task.processors_required) {
        // Filling with snapshot with 'indexes'
        for (int i = 0; i < current_task.processors_required; ++i) {
          snap[snap_p] = current_task.index;
          snap_p++;
        }
        tasks_blacklist[current_task.index] = true;
        cpu_bursts[current_task.index]--;
      }
    }

    printf(" %2d | ", t);
    for (int processor_index = 0; processor_index < processors_limit; ++processor_index) {
      printf("[");
      if (snap[processor_index] == -1) {
        printf(" ");
        average_holing_time++;
      } else {
        printf("%c", snap[processor_index] + (int)'A');
        average_working_time++;
      }
      printf("]");
    }
    printf("\n");

    bool all_tasks_are_done = true;
    for (int task_index = 0; task_index < total_tasks; ++task_index) {
      Task current_task = *(p_tasks[task_index]);
      if (cpu_bursts[current_task.index] != 0) {
        all_tasks_are_done = false;
      }
    }
    if (all_tasks_are_done) {
      printf("    |\n    |\n    t\n    i\n    m\n    e\n    |\n    v\n\n");
      printf("Time to do all the tasks is %d units.\n", t);
      printf("Average working time is %d (%.1lf%) units and average holding time is %d (%.1lf%) units.\n",
             average_working_time,
             (double)100 * average_working_time / (t+1) / processors_limit,
             average_holing_time,
             (double)100 * average_holing_time / (t+1) / processors_limit);
      break;
    }
  }

  return (EXIT_SUCCESS);
}
