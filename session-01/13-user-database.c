// TASK: User database (hash table)
// STATUS: file I/O not working yet
// MARK: PENDING

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct _Node {
  char *key;
  char *value;
  struct _Node *next;
} node;

typedef struct _Dict {
  int HASH_LENGTH;
  node **data;
} dict;

int hash(char *key, int hash_length) {
  int d = 0;
  int p = 1337;
  for (int i = 0; i < strlen(key); ++i) {
    d += key[i] * (int)pow(p, i);
    d %= (int)pow(2, hash_length);
  }
  return d;
}

dict* newDict(int hash_length) {
  dict *hash_table = (dict*)malloc(sizeof(dict));
  hash_table->HASH_LENGTH = hash_length;
  hash_table->data = malloc(sizeof(node *) * (int)pow(2, hash_table->HASH_LENGTH));

  for (int i = 0; i < (int)pow(2, hash_table->HASH_LENGTH); i++) {
    hash_table->data[i] = NULL;
  }

  return hash_table;
}

bool needs_replace(node *current_node, node *new_node, node *previous_node, char *key) {
  if (current_node->key == key) {
    if (previous_node) {
      previous_node->next = new_node;
    }
    new_node->next = current_node->next;
    free(current_node);
    return true;
  }
  return false;
}

node *append(node *head_node, char *key, char *value) {
  node *new_node = malloc(sizeof(node *));
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;

  node *current_node = head_node;
  node *previous_node = NULL;

  if (head_node) {
    while (current_node->next) {
      if (needs_replace(current_node, new_node, previous_node, key)) {
        return head_node;
      }
      previous_node = current_node;
      current_node = current_node->next;
    }

    if (previous_node) {
      previous_node->next = new_node;
    } else {
      if (needs_replace(head_node, new_node, previous_node, key)) {
        return new_node;
      }
      head_node->next = new_node;
    }
    return head_node;
  } else {
    return new_node;
  }
}

void insert(dict *d, char *key, char *value) {
  int bucket = hash(key, d->HASH_LENGTH);
  d->data[bucket] = append(d->data[bucket], key, value);
}

char *search_list(node *current_node, char *key) {
  node *previous_node = NULL;
  while (current_node) {
    if (current_node->key = key) {
      return current_node->value;
    }
    previous_node = current_node;
    current_node = current_node->next;
  }
}

void displayDict(dict *d) {
  printf("dict{\n");
  for (int i = 0; i < (int)pow(2, d->HASH_LENGTH); ++i) {
    if (d->data[i] != NULL) {
      printf("(%d): %s -> %s\n", i, d->data[i]->key, d->data[i]->value);
    }
  }
  printf("}\n");
}

char *get(dict *d, char *key) {
  if (d->data[hash(key, d->HASH_LENGTH)] != NULL) {
    node *current_node = d->data[hash(key, d->HASH_LENGTH)];
    return search_list(current_node, key);
  } else {
    return "NULL";
  }
}

int main() {
  dict *first_dict = newDict(20);

  insert(first_dict, "a\0", "animal\0");
  insert(first_dict, "b\0", "ball\0");
  insert(first_dict, "s\0", "sea lion\0");
  insert(first_dict, "t\0", "table\0");

  printf("a -> %s\n", get(first_dict, "a"));
  printf("b -> %s\n", get(first_dict, "b"));
  printf("s -> %s\n", get(first_dict, "s"));
  printf("t -> %s\n", get(first_dict, "t"));
  printf("c -> %s\n", get(first_dict, "c"));

  return 0;
}
