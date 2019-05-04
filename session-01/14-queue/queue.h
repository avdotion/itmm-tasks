#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
  char *value;
  struct _Node *next;
} node;

typedef struct _Queue {
  node *head;
  node *tail;
} queue;

node* newNode(char *value);
queue* newQueue();
void pushQueue(queue *queue, char *value);
bool isEmptyQueue(queue *queue);
char* popQueue(queue *queue);
