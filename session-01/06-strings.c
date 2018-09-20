#include <stdio.h>

int main() {
  char symbol;

  unsigned int sentences[100] = {0};
  unsigned int words[100] = {0};

  unsigned int letters_in_last_word = 0;
  unsigned int words_in_last_sentence = 0;
  unsigned int current_sentence = 0;
  unsigned int current_word = 0;

  // Count all words in sentences and all letters in word
  while ((symbol = getchar()) != EOF) {
    if ((symbol == ' ' || symbol == '\n')&& letters_in_last_word) {
      words[current_word] = letters_in_last_word;
      letters_in_last_word = 0;
      current_word++;
      words_in_last_sentence++;
    } else if (symbol == '.' || symbol == '?' || symbol == '!') {
      if (letters_in_last_word) {
        words[current_word] = letters_in_last_word;
        letters_in_last_word = 0;
        current_word++;
        words_in_last_sentence++;
      }
      sentences[current_sentence] = words_in_last_sentence;
      words_in_last_sentence = 0;
      current_sentence++;
    } else {
      letters_in_last_word++;
    }
  }

  if (letters_in_last_word) {
    words[current_word] = letters_in_last_word;
    letters_in_last_word = 0;
    current_word++;
    words_in_last_sentence++;
  }

  if (words_in_last_sentence) {
    sentences[current_sentence] = words_in_last_sentence;
    words_in_last_sentence = 0;
    current_sentence++;
  }

  printf("\n");
  // Display the words chart
  for (unsigned int i = 0; i < current_word + 1; ++i) {
    for (unsigned int stars = 0; stars < words[i]; ++stars) {
      printf("*");
    }
    printf("\n");
  }

  // Display the sentences chart
  unsigned int longest_sentence_length = 0;
  for (unsigned int i = 0; i < current_sentence; ++i) {
    if (sentences[i] > longest_sentence_length) {
      longest_sentence_length = sentences[i];
    }
  }

  for (int height = longest_sentence_length; height >= 0; height--) {
    for (unsigned int i = 0; i < current_sentence; ++i) {
      if (height < sentences[i]) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
