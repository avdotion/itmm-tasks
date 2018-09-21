// TASK: Inner loops
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
  srand((unsigned int)time(NULL));
  bool is_user_want_to_exit = false;
  int MAX_ATTEMPTS = 5;

  char buffer[50];
  char *ptr;

  // Mainloop
  do {
    int attempts = 0;
    int number = rand() % 100;
    bool game_over = false;
    bool user_won = false;

    // Step loop
    do {
      int user_guess;
      printf("Try to guess the number between 0 and 99: ");
      scanf("%s", buffer);
      user_guess = (int)strtol(buffer, &ptr, 10);

      if (user_guess == number) {
        printf("You are totally right! (attemps = %d)\n", attempts);
        user_won = true;
      } else {
        if (user_guess > number) {
          printf("The number is less than your guess\n");
        } else {
          printf("The number is larger than your guess\n");
        }
      }
      attempts++;
      if (attempts >= MAX_ATTEMPTS) {
        printf("Game Over!\nThe number was %d\n", number);
        game_over = true;
      }
    } while (!user_won && !game_over);

    printf("Want to continue (Y/n)?\n");
    char user_choice;
    scanf(" %c", &user_choice);
    if (user_choice == 'N' || user_choice == 'n') {
      is_user_want_to_exit = true;
    }
  } while (!is_user_want_to_exit);
}
