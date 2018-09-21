// TASK: IF statement, typecasting
// STATUS: DONE
// MARK: PENDING

#include <stdio.h>
#include <stdbool.h>

int main() {
  int day, month, year;
  printf("Enter date in format dd/mm/yyyy: ");
  bool wrong_input = false;
  do {
    if (wrong_input) {
      printf("Oh, input date is not correct. Please, try again: ");
    }
    scanf("%d/%d/%d", &day, &month, &year);
    wrong_input = true;
  } while (!(1 <= day && day <= 31 &&
             1 <= month && month <= 12 &&
             1582 <= year && year <= 4902)
  );

  month = (month - 3) % 12 + 1;

  if (month <= 0) {
    month += 12;
  }

  int first_two_year_letters = year / 100;
  int last_two_year_letters = year % 100;

  int weekday = (int)(2.6 * month - 0.2) + day +
    last_two_year_letters + (last_two_year_letters / 4) +
    (first_two_year_letters / 4) - 2 * first_two_year_letters;

  // Offset
  weekday--;
  if (weekday < 0) {
    weekday += 7;
  }
  weekday %= 7;

  switch (weekday) {
    case (0):
      printf("Monday\n");
      break;
    case (1):
      printf("Tuesday\n");
      break;
    case (2):
      printf("Wednesday\n");
      break;
    case (3):
      printf("Thursday\n");
      break;
    case (4):
      printf("Friday\n");
      break;
    case (5):
      printf("Saturday\n");
      break;
    case (6):
      printf("Sunday\n");
      break;
    default:
      printf("Oops, something went wrong...\n");
      break;
  }
  return 0;
}
