#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stringcmp(const void *a, const void *b) {
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
}

int main() {
  const size_t MAX_NAME = 50;
  char name[MAX_NAME];

  int strings_counter = 0;
  char **input = NULL;
  char **more_input = NULL;

  do {
    fgets(name, 100, stdin);
    strings_counter++;
    more_input = (char **)realloc(input, strings_counter * sizeof(name));

    if (more_input != NULL) {
      input = more_input;
      input[strings_counter-1] = strdup(name);
    }

  } while (strcmp(name, "\n"));

  qsort(input, strings_counter-1, sizeof(char *), stringcmp);

  printf("Sorted strings:\n");

  for (int i = 0; i < strings_counter-1; i++)
    printf("%s", input[i]);
/*
  for (int i = 0; i < num; i++) {
    free(input[i]);
  }

  free(input);


*/
}
