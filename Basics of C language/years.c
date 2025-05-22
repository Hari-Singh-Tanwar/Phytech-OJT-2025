#include <stdio.h>

int main() {
  int Days, Y, W, D;

  printf("Enter the Days\n");
  scanf("%d", &Days);
  Y = Days / 365;
  W = (Days - (365 * Y)) / 7;
  D = Days - (365 * Y) - (W * 7);

  printf("In %d days their are %d years, %d weaks and %d days\n", Days, Y, W,
         D);

  return 0;
}
