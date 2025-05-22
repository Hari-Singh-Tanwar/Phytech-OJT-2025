#include <stdio.h>

int main() {
  int a = 5, b = 10;

  printf("Before Swaping a = %d, b = %d\n", a, b);

  a = a ^ b;
  b = a ^ b;
  a = a ^ b;
  printf("After Swaping a = %d, b = %d\n", a, b);
  return 0;
}
