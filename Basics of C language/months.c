#include <stdio.h>

int main() {
  int month;
  printf("Enter a mounth number\n");
  scanf("%d", &month);

  if (month <= 12) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
        month == 10 || month == 12) {
      printf("number of days in the %d month are 31", month);
    } else if (month == 2) {
      printf("the number of days in the %d month are 28", month);
    } else {
      printf("The number of days in the %d month are 30", month);
    }
  }
  else{
    printf("enter valid number\n");
  }
  return 0;
}
