// TASK: Strings sorting
// STATUS: DONE
// MARK: CALLED-DOWN

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BUFFER_SIZE 50

int compare_strings_case(char *s1, char *s2) {
  while (*s1 && *s2) {
    if (tolower(*s1) != tolower(*s2)) {
      break;
    }
    ++s1;
    ++s2;
  }
  return tolower(*s1) - tolower(*s2);
}

int compare_strings(char *s1, char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) {
      break;
    }
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

int main() {
  char buffer[MAX_BUFFER_SIZE];

  int strings_counter = 0;
  char **strings = NULL;
  char **_strings = NULL;

  printf("Just start typing any items down here...\n");

  while (1) {
    fgets(buffer, MAX_BUFFER_SIZE, stdin);
    
    if (buffer[0] == '\n') {
      break;
    }
    
    strings_counter++;
    _strings = (char **)realloc(strings, strings_counter * sizeof(buffer));

    if (_strings != NULL) {
      strings = _strings;
      strings[strings_counter-1] = strdup(buffer);
    }
  }

  char ***p_strings = (char ***)malloc(strings_counter * sizeof(char **));
  for (int i = 0; i < strings_counter; ++i) {
    p_strings[i] = &strings[i];
  }

  printf("\n");

  char **temp = NULL;

  for (int i = 0; i < strings_counter; ++i) {
    for (int j = 0; j < strings_counter - i - 1; ++j) {
      if (compare_strings(*p_strings[j], *p_strings[j + 1]) > 0) {
        temp = p_strings[j];
        p_strings[j] = p_strings[j + 1];
        p_strings[j + 1] = temp; 
      }
    }
  }

  printf("The list before sorting:\n");
  for (int i = 0; i < strings_counter; ++i) {
    printf("%s", strings[i]);
  }
  printf("\n");

  printf("The list after sorting:\n");
  for (int i = 0; i < strings_counter; ++i) {
    printf("%s", *p_strings[i]);
  }
}
