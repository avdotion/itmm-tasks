// TASK: Merge sort
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdlib.h>

// Dynamically growing array structure
typedef struct {
  int *data;
  size_t size;
  size_t _reserved_size;
} array;

void initArray(array *a, size_t initial_size) {
  a->data = (int *)malloc(initial_size * sizeof(int));
  a->size = 0;
  a->_reserved_size = initial_size;
}

void insertArray(array *a, int item) {
  if (a->size == a->_reserved_size) {
    a->_reserved_size *= 2;
    a->data = (int *)realloc(a->data, a->_reserved_size * sizeof(int));
  }
  a->data[a->size++] = item;
}

void freeArray(array *a) {
  free(a->data);
  a->data = NULL;
  a->size = a->_reserved_size = 0;
}

void printArray(array *a) {
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

void selectionSort(array *);

array merge(array *a, array *b) {
  array c;
  initArray(&c, 1);
  int i = 0;
  int j = 0;

  while (i < a->size && j < b->size) {
    if (a->data[i] <= b->data[j]) {
      insertArray(&c, a->data[i]);
      i++;
    } else {
      insertArray(&c, b->data[j]);
      j++;
    }
  }
  for (; i < a->size; ++i) {
    insertArray(&c, a->data[i]);
  }
  for (; j < b->size; ++j) {
    insertArray(&c, b->data[j]);
  }
  return c;
}

void mergeSort(array *a) {
  if (1 < a->size && a->size < 5) {
    selectionSort(a);
  } else if (a->size >= 5) {
    int middle = (int)(a->size / 2);

    array l;
    initArray(&l, 1);
    for (int i = 0; i < middle; ++i) {
      insertArray(&l, a->data[i]);
    }

    array r;
    initArray(&r, 1);
    for (int i = middle; i < a->size; ++i) {
      insertArray(&r, a->data[i]);
    }

    mergeSort(&l);
    mergeSort(&r);

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

void selectionSort(array *a) {
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
  array simple_array;
  initArray(&simple_array, 1);
  for (int i = 60; i >= 0; --i) {
    insertArray(&simple_array, i);
  }
  printArray(&simple_array);
  mergeSort(&simple_array);
  printArray(&simple_array);

}
