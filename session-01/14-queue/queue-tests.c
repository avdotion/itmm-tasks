#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() {
  queue *common_lifo = newQueue();
  queue *left_lifo = newQueue();
  queue *right_lifo = newQueue();

  pushQueue(common_lifo, "Alexander");
  pushQueue(common_lifo, "Sofiya");
  pushQueue(common_lifo, "Maxim");
  pushQueue(common_lifo, "Mariya");
  pushQueue(common_lifo, "Artem");
  pushQueue(common_lifo, "Anna");
  pushQueue(common_lifo, "Mikhail");
  pushQueue(common_lifo, "Anastasia");
  pushQueue(common_lifo, "Daniil");
  pushQueue(common_lifo, "Vikroriya");
  pushQueue(common_lifo, "Ivan");
  pushQueue(common_lifo, "Yelizaveta");
  pushQueue(common_lifo, "Dmitry");
  pushQueue(common_lifo, "Polina");
  pushQueue(common_lifo, "Kirill");
  pushQueue(common_lifo, "Alisa");
  pushQueue(common_lifo, "Andrey");
  pushQueue(common_lifo, "Dariya");
  pushQueue(common_lifo, "Yegor");
  pushQueue(common_lifo, "Alexandra");

  for (int i = 0; !isEmptyQueue(common_lifo); ++i) {
    if (i % 2 == 0) {
      pushQueue(left_lifo, popQueue(common_lifo));
    } else {
      pushQueue(right_lifo, popQueue(common_lifo));
    }
  }

  printf("Left queue:\n");
  while (!isEmptyQueue(left_lifo)) {
    printf("%s \n", popQueue(left_lifo));
  }
  printf("\n");
  printf("Right queue:\n");
  while (!isEmptyQueue(right_lifo)) {
    printf("%s \n", popQueue(right_lifo));
  }

  return 0;
}
