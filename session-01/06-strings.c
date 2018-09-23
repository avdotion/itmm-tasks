// TASK: C-Strings
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>

int main() {
  char symbol;

  // Words in every i-sentence
  int words_counter[100] = {0};
  // Letters in every i-word
  int letters_counter[100] = {0};

  int letters_in_last_word = 0;
  int words_in_last_sentence = 0;

  // Current entities counters
  int sentences_count = 0;
  int word_count = 0;

  // Count all words in sentences and all letters in word
  while ((symbol = getchar()) != EOF) {
    if ((symbol == ' ' || symbol == '\n') && letters_in_last_word) {
      letters_counter[word_count++] = letters_in_last_word;
      letters_in_last_word = 0;
      words_in_last_sentence++;
    } else if (symbol == '.' || symbol == '?' || symbol == '!') {
      if (letters_in_last_word) {
        letters_counter[word_count++] = letters_in_last_word;
        letters_in_last_word = 0;
        words_in_last_sentence++;
      }
      words_counter[sentences_count] = words_in_last_sentence;
      words_in_last_sentence = 0;
      sentences_count++;
    } else {
      letters_in_last_word++;
    }
  }

  if (letters_in_last_word) {
    letters_counter[word_count++] = letters_in_last_word;
    letters_in_last_word = 0;
    words_in_last_sentence++;
  }

  if (words_in_last_sentence) {
    words_counter[sentences_count++] = words_in_last_sentence;
    words_in_last_sentence = 0;
  }

  printf("\n");
  // Display the words chart
  for (int i = 0; i < word_count + 1; ++i) {
    for (int stars = 0; stars < letters_counter[i]; ++stars) {
      printf("*");
    }
    printf("\n");
  }

  // Display the sentences chart
  int longest_sentence_length = 0;
  for (int i = 0; i < sentences_count; ++i) {
    if (words_counter[i] > longest_sentence_length) {
      longest_sentence_length = words_counter[i];
    }
  }

  for (int height = longest_sentence_length; height >= 0; height--) {
    for (int i = 0; i < sentences_count; ++i) {
      if (height < words_counter[i]) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
