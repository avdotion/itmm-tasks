// TASK: Preemptive multitasking
// STATUS: DONE
// MARK: PASSED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char INACTIVE_MARKER = '-';
char ACTIVE_MARKER = '*';

int get_int() {
  char buffer[20];
  char *ptr;

  scanf("%s", buffer);
  return (int)strtol(buffer, &ptr, 10);
}

typedef struct Task {
  int index;
  int cpu_burst;
} Task;

typedef struct LinkedListNode {
  void* data;
  struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* newLinkedListNode(void* data) {
  LinkedListNode *linked_list_node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
  linked_list_node->data = data;
  linked_list_node->next = NULL;
  return linked_list_node;
}

typedef struct LinkedList {
  int size;
  LinkedListNode* chain;
} LinkedList;

LinkedList* newLinkedList() {
  LinkedList *linked_list = (LinkedList*)malloc(sizeof(LinkedList));
  linked_list->chain = newLinkedListNode("_HEAD");
  linked_list->chain->next = newLinkedListNode("_TAIL");
  linked_list->size = 0;
  return linked_list;
}

void* getByIndexLinkedList(LinkedList* linked_list, int index) {
  if (index <= linked_list->size) {
    LinkedListNode* current = linked_list->chain->next;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->data;
  } else {
    return NULL;
  }
}

bool appendLinkedList(void* data, LinkedList* linked_list, int index) {
  if (index > linked_list->size) {
    return false;
  } else {
    LinkedListNode* current = linked_list->chain;
    for (int i = 0; i < index; ++i) {
      current = current->next;
    }
    LinkedListNode* node = newLinkedListNode(data);
    node->next = current->next;
    current->next = node;
  }
  linked_list->size++;
  return true;
}

bool removeLinkedList(LinkedList* linked_list, int index) {
  if (index >= linked_list->size) {
    return false;
  } else {
    LinkedListNode* current = linked_list->chain;
    for (int i = 0; i <= index; ++i) {
      current = current->next;
    }
    current->data = current->next->data;
    current->next = current->next->next;
  }
  linked_list->size--;
  return true;
}

void printLinkedList(LinkedList* linked_list, char* (*handler)(void*)) {

  LinkedListNode* current = linked_list->chain;
  for (int i = 0; i < linked_list->size; ++i) {
    current = current->next;
    char* t = (*handler)(current->data);
    printf("%s", t);
  }
  printf("\n");
}

char* toStringDefault(void* ptr) {
  static char buffer[10];
  sprintf(buffer, "%s", ptr);
  return buffer;
}

char* toCharDefault(void* ptr) {
  static char buffer[10];
  sprintf(buffer, "%c", *(char*)ptr);
  return buffer;
}

int main() {
  printf("What is the quant? ");
  int time_quant = get_int();
  if (time_quant <= 0) {
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
  printf("\t- CPU-burst\n");

  LinkedList* queue = newLinkedList();

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
  }

  // Printing a prepeared data table
  printf("[label]\t[CPU-b]\n");
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    Task current_task = tasks[task_index];
    printf("%c\t%d\n", current_task.index + (int)'A',
                                   current_task.cpu_burst);
  }

  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    appendLinkedList(&tasks[task_index], queue, queue->size);
  }


  // Time to choose an algorithm!
  //
  // printf("Choose one of the algorithms ('fcfs' (default) or 'sjf'): ");
  // char algorithm[20];
  // scanf("%s", algorithm);
  //
  // if (strcmp(algorithm, "sjf") == 0) {
  //   printf("The 'sjf' has been launched...\n");
  //   qsort(p_tasks, total_tasks, sizeof(Task*), compare_tasks_cpu_bursts);
  // } else {
  //   printf("The 'fcfs' has been launched...\n");
  // }

  int *cpu_bursts_left = malloc(total_tasks * sizeof(int));
  for (int task_index = 0; task_index < total_tasks; ++task_index) {
    Task current_task = tasks[task_index];
    cpu_bursts_left[current_task.index] = current_task.cpu_burst;
  }

  LinkedList* graph[total_tasks];
  for (int i = 0; i < total_tasks; ++i) {
    graph[i] = newLinkedList();
  }

  int average_holding_time = 0;

  bool is_task_done[total_tasks];
  for (int i = 0; i < total_tasks; ++i) {
    is_task_done[i] = false;
  }

  while (queue->size > 0) {
    bool task_removed = false;
    Task* current_task = (Task *)getByIndexLinkedList(queue, 0);
    for (int i = 0; i < time_quant; ++i) {
      // Fill with __empty spaces__
      for (int k = 0; k < total_tasks; ++k) {
        if (!is_task_done[k]) {
          average_holding_time++;
        }
        appendLinkedList(&INACTIVE_MARKER, graph[k], graph[k]->size);
      }
      removeLinkedList(graph[current_task->index], graph[current_task->index]->size - 1);
      appendLinkedList(&ACTIVE_MARKER, graph[current_task->index], graph[current_task->index]->size);

      cpu_bursts_left[current_task->index]--;
      if (cpu_bursts_left[current_task->index] <= 0) {
        task_removed = true;
        is_task_done[current_task->index] = true;
        removeLinkedList(queue, 0);
        break;
      }
    }
    if (!task_removed) {
      removeLinkedList(queue, 0);
      if (cpu_bursts_left[current_task->index] > 0) {
        appendLinkedList(current_task, queue, queue->size);
      }
    }
  }

  printf("Graph:\n");

  for (int i = 0; i < total_tasks; ++i) {
    printf("%c: ", (int)'A' + i);
    printLinkedList(graph[i], &toCharDefault);
  }

  printf("Average working time: %d; average holding time: %d\n",
    graph[0]->size,
    average_holding_time
  );

}
