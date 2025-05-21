#include <stdio.h>

int main() {
int odd = 1;
  for (int i = 1; i <= 30; i++) {
    odd = odd + 2;
    printf("%d\n", odd);
  }
  return 0;
}
