#include <stdio.h>
#include <unistd.h>

int main() {
  int cpid = fork();
  if (cpid == 0)
    while (1)
      putchar('x');
  else
    while (1)
      putc('o', stdout);
  return 0;
}
