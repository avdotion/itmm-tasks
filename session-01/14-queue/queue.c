#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

node* newNode(char *value) {
  node *n = (node*)malloc(sizeof(node));
  n->value = value;
  n->next = NULL;
  return n;
}

queue* newQueue() {
  queue *q = (queue*)malloc(sizeof(queue));
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void pushQueue(queue *queue, char *value) {
  node *node = newNode(value);
  if (queue->head == NULL) {
    queue->head = node;
  } else {
    queue->tail->next = node;
  }
  queue->tail = node;
}

bool isEmptyQueue(queue *queue) {
  if (queue->head == NULL) {
    return true;
  }
  return false;
}

char* popQueue(queue *queue) {
  if (isEmptyQueue(queue)) {
    printf("Can't pushQueue this queue\n");
    exit(EXIT_FAILURE);
  }
  node *node = queue->head;
  queue->head = node->next;
  if (isEmptyQueue(queue)) {
    queue->tail = NULL;
  }
  if (node != NULL) {
    char *value = node->value;
    free(node);
    return value;
  }
  exit(EXIT_FAILURE);
}
