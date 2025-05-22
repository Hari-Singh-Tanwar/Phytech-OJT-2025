#include <stdio.h>

int main() {
  int first, second, third;
  printf("Enter 3 integers \n");
  scanf("%d %d %d", &first, &second, &third);

  if (first > second && first > third) {
    printf("The largest number is %d\n", first);
  } else if (second > third) {
    printf("The largesrt number is %d\n", second);
  } else {
    printf("The largest number is %d", third);
  }
  return 0;
}
