#include <stdio.h>

int main() {
  int num = 0, bit;
  int started = 0;
  printf("Enter a number\n");
  scanf("%d", &num);
  printf("The Binary value of %d is : ", num);

  for (int i = 31; i >= 0; i--) {
    bit = (num >> i) & 1;
    printf("%d ", bit);

    if (num < 0) {
      printf("%d", bit);
    } else {
      if (bit == 1) {
        started = 1;
      }
      if (started) {
        printf("%d", bit);
      }
    }
  }
  if (num == 0) {
    printf("0");
  }
  printf("\n");
  return 0;
}
