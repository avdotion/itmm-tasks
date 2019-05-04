// TASK: Non-Preemptive multitasking
// STATUS: DONE
// MARK: PASSED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

typedef struct Task {
  int index;
  int cpu_burst;
  int processors_required;
  bool was_launched;
  int position;
} Task;

int compare_tasks_cpu_bursts(const void* a, const void* b) {
    Task *left_task = *(Task**)a;
    Task *right_task = *(Task**)b;

    if (left_task->cpu_burst < right_task->cpu_burst)
        return -1;
    else if (left_task->cpu_burst > right_task->cpu_burst)
        return 1;
    else
        return 0;
}

int main() {
  printf("How many processors are available? ");
  int processors_limit = get_int();
  if (processors_limit <= 0) {
    // Exception handling
    printf("An error occurred!\n");
    return (EXIT_FAILURE);
  }

  printf("How many tasks do you want to lauch? ");
  int total_tasks = get_int();
  if (total_tasks <= 0) {
    // Exception handling
    printf("An error occurred!\n");
    return (EXIT_FAILURE);
  }

  printf("Every task must has the following atributes:\n");
  printf("\n- CPU-burst\n- processors\n");

  Task* tasks = malloc(total_tasks * sizeof *tasks);
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    tasks[task_index].index = task_index;

    printf("Enter the %d task CPU-burst: ", task_index + 1);
    tasks[task_index].cpu_burst = get_int();
    if (tasks[task_index].cpu_burst <= 0) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }

    printf("Enter the %d task processors required: ", task_index + 1);
    tasks[task_index].processors_required = get_int();
    if (!(0 <= tasks[task_index].processors_required &&
               tasks[task_index].processors_required <= processors_limit)) {
      // Exception handling
      printf("An error occurred!\n");
      return (EXIT_FAILURE);
    }
  }

  Task** p_tasks = (Task **)malloc(total_tasks * sizeof(Task *));
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    p_tasks[task_index] = &tasks[task_index];
  }

  // Time to choose an algorithm!

  printf("Choose one of the algorithms ('fcfs' (default) or 'sjf'): ");
  char algorithm[20];
  scanf("%s", algorithm);

  if (strcmp(algorithm, "sjf") == 0) {
    printf("The 'sjf' has been launched...\n");
    qsort(p_tasks, total_tasks, sizeof(Task*), compare_tasks_cpu_bursts);
  } else {
    printf("The 'fcfs' has been launched...\n");
  }

  // Printing a prepeared data table
  printf("[label]\t[CPU-b]\t[procs]\n");
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    Task current_task = *(p_tasks[task_index]);
    printf("%c\t%d\t%d\t%d\t%d\n", current_task.index + (int)'A',
                                   current_task.cpu_burst,
                                   current_task.processors_required);
  }

  int cpu_bursts[total_tasks];
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    Task current_task = *(p_tasks[task_index]);
    cpu_bursts[current_task.index] = current_task.cpu_burst;
  }

  // Non-preemptive feature
  // Force add to the snap already launched tasks
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    tasks[task_index].was_launched = false;
    tasks[task_index].position = -1;
  }

  int average_working_time = 0;
  int average_holing_time = 0;
  printf("    +---------------------processors-->\n");
  // t - time on the timeline axis
  for (int t = 0; ; ++t) {
    // Snapshot - a single row in a timeline
    int snap[processors_limit];
    for (int i = 0; i < processors_limit; ++i) {
      snap[i] = -1;
    }
    int snap_p = 0;

    // A task can be launched only once in a row
    bool tasks_blacklist[total_tasks];
    for (int i = 0; i < processors_limit; ++i) {
      tasks_blacklist[i] = false;
    }

    for (int task_index = 0; task_index < total_tasks; ++task_index) {
      Task current_task = *(p_tasks[task_index]);
      if (current_task.was_launched &&
          cpu_bursts[current_task.index] > 0) {
        for (int i = 0; i < current_task.processors_required; ++i) {
          snap[i + current_task.position] = current_task.index;
        }
        tasks_blacklist[current_task.index] = true;
        cpu_bursts[current_task.index]--;
      }
    }

    for (int task_index = 0; task_index < total_tasks; ++task_index) {
      Task current_task = *(p_tasks[task_index]);
      // Warning: a miserable thing to use 'task_index' in squared brackets
      if (!tasks_blacklist[current_task.index] &&
          cpu_bursts[current_task.index] > 0 &&
          processors_limit - snap_p >= current_task.processors_required) {
        bool is_blocked = false;
        for (int i = 0; i < current_task.processors_required; ++i) {
          if (snap[snap_p+i] != -1) {
            is_blocked = true;
          }
        }
        // Filling with snapshot with 'indexes'
        if (!is_blocked) {
          tasks[current_task.index].position = snap_p;
        }
        for (int i = 0; i < current_task.processors_required; ++i) {
          if (!is_blocked) {
            snap[snap_p] = current_task.index;
          }
          snap_p++;
        }
        if (!is_blocked) {
          tasks[current_task.index].was_launched = true;
          tasks_blacklist[current_task.index] = true;
          cpu_bursts[current_task.index]--;
        }
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

}
