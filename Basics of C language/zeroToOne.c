#include <stdio.h>

int main() {
 unsigned long long num, mod = 0;
  int digit, place = 1;

  printf("Enter a number\n");
  scanf("%llu", &num);

  if (num == 0) {
    mod = 1;
  } else {
    while (num > 0) {
      digit = num % 10;
      if (digit == 0) {
        digit = 1;
      }
      mod += digit * place;
      place *= 10;
      num /= 10;
    }
  }

  printf("The modified number is %llu", mod);
  return 0;
}
