// TASK: Merge sort
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDOM_ARRAY_SIZE 10

// Dynamically growing array structure
typedef struct {
  int *data;
  size_t size;
  size_t _reserved_size;
} array;

void init_array(array *a, size_t initial_size) {
  a->data = (int *)malloc(initial_size * sizeof(int));
  a->size = 0;
  a->_reserved_size = initial_size;
}

void insert_array(array *a, int item) {
  if (a->size == a->_reserved_size) {
    a->_reserved_size *= 2;
    a->data = (int *)realloc(a->data, a->_reserved_size * sizeof(int));
  }
  a->data[a->size++] = item;
}

void free_array(array *a) {
  free(a->data);
  a->data = NULL;
  a->size = a->_reserved_size = 0;
}

void print_array(array *a) {
  if (a->size) {
    printf("[");
    for (int i = 0; i < a->size - 1; ++i) {
      printf("%d, ", a->data[i]);
    }
    printf("%d]\n", a->data[a->size-1]);
  } else {
    printf("[]\n");
  }
}

// MergeSort algorithm

void selection_sort(array *);

array merge(array *a, array *b) {
  array c;
  init_array(&c, 1);
  int i = 0;
  int j = 0;

  while (i < a->size && j < b->size) {
    if (a->data[i] <= b->data[j]) {
      insert_array(&c, a->data[i]);
      i++;
    } else {
      insert_array(&c, b->data[j]);
      j++;
    }
  }
  for (; i < a->size; ++i) {
    insert_array(&c, a->data[i]);
  }
  for (; j < b->size; ++j) {
    insert_array(&c, b->data[j]);
  }
  return c;
}

void merge_sort(array *a) {
  if (1 < a->size && a->size < 5) {
    selection_sort(a);
  } else if (a->size >= 5) {
    int middle = (int)(a->size / 2);

    array l;
    init_array(&l, 1);
    for (int i = 0; i < middle; ++i) {
      insert_array(&l, a->data[i]);
    }

    array r;
    init_array(&r, 1);
    for (int i = middle; i < a->size; ++i) {
      insert_array(&r, a->data[i]);
    }

    merge_sort(&l);
    merge_sort(&r);

    array c = merge(&l, &r);
    *a = c;
  }
}

// Modification

void swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void selection_sort(array *a) {
  for (int j = 0; j < a->size - 1; ++j) {
    int iMin = j;
    for (int i = j + 1; i < a->size; ++i) {
      if (a->data[i] < a->data[iMin]) {
        iMin = i;
      }
    }
    if (iMin != j) {
      swap(&a->data[j], &a->data[iMin]);
    }
  }
}


int main() {
  srand(time(NULL));
  char buffer[100];
  char *ptr;
  
  array simple_array;
  init_array(&simple_array, 1);
  
  for (int i = 0; i < RANDOM_ARRAY_SIZE; ++i) {
    insert_array(&simple_array, rand() % 100);
  }

  // Fool protection!

  // printf("How many values do you want to sort?\n");
  // scanf("%s", buffer);
  // int numbers_count = (int)strtol(buffer, &ptr, 10);

  // printf("Enter values you want to sort down here...\n");
  // for (int i = 0; i < numbers_count; ++i) {
  //   scanf("%s", buffer);
  //   insert_array(&simple_array, (int)strtol(buffer, &ptr, 10));
  // }

  print_array(&simple_array);
  merge_sort(&simple_array);
  print_array(&simple_array);

}
