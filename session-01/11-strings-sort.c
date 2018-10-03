// TASK: Strings sorting
// STATUS: DONE
// MARK: CALLED-DOWN

// TODO:
// [ ] redeclare cmp for strings

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp_p_strings(const void *a, const void *b) {
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
}

int main() {
  const size_t MAX_NAME = 50;
  char name[MAX_NAME];

  int strings_counter = 0;
  char **input = NULL;
  char **another_input = NULL;

  do {
    fgets(name, 100, stdin);
    strings_counter++;
    another_input = (char **)realloc(input, strings_counter * sizeof(name));

    if (another_input != NULL) {
      input = another_input;
      input[strings_counter-1] = strdup(name);
    }

  } while (strcmp(name, "\n") != 0);

  qsort(input, (int)(strings_counter - 1), sizeof(char *), cmp_p_strings);

  printf("Sorted strings:\n");

  for (int i = 0; i < strings_counter-1; i++)
    printf("%s", input[i]);
}
