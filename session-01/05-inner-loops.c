#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
  srand(time(NULL));
  bool is_user_want_to_exit = false;
  int MAX_ATTEMPS = 5;
  do {
    // Main loop
    int attempts = 0;
    int number = rand() % 100;
    bool game_over = false;
    bool user_won = false;
    /*
    printf("Enter attempts number: ");
    scanf("%d", &attempts);
    */
    do {
      // Step loop
      int user_guess;
      printf("Try to guess the number between 0 and 99: ");
      scanf("%d", &user_guess);

      if (user_guess == number) {
        printf("You are totally right! (attemps = %d)\n", attemps);
        user_won = true;
      } else {
        if (user_guess > number) {
          printf("The number is less than your guess\n");
        } else {
          printf("The number is larger than your guess\n");
        }
      }
      attempts++;
      if (attempts < MAX_ATTEMPS) {
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
