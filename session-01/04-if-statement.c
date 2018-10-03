// TASK: IF statement, typecasting
// STATUS: DONE
// MARK: CALLED-DOWN AGAIN

#include <stdio.h>
#include <stdbool.h>

bool is_leap(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main() {
  int day, month, year;

  int MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  bool is_data_correct;
  do {
    printf("Enter date in format dd/mm/yyyy: ");
    scanf("%d/%d/%d", &day, &month, &year);

    is_data_correct = true;

    if (!(1 <= month && month <= 12)) {
      printf("Entered month isn't correct!\n");
      is_data_correct = false;
    }

    if (!(1582 <= year && year <= 4902)) {
      printf("Entered year should be between 1582 and 4902!\n");
      is_data_correct = false;
    }

    if (!((1 <= day && day <= MONTHS[month-1]) ||
          (month == 2 && is_leap(year) && 1 <= day && day <= MONTHS[month-1] + 1))) {
      printf("The day %d isn't exist in that month!\n", day);
      is_data_correct = false;
    }

  } while (!is_data_correct);

  if (month == 0 || month == 1) {
    year--;
  }

  month = (month - 3) % 12 + 1;

  while (month <= 0) {
    month += 12;
  }

  int first_two_year_letters = year / 100;
  int last_two_year_letters = year % 100;

  int weekday = (int)(2.6 * month - 0.2) + day +
    last_two_year_letters + (last_two_year_letters / 4) +
    (first_two_year_letters / 4) - 2 * first_two_year_letters;

  // Offset
  weekday--;
  while (weekday < 0) {
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
