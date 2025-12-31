#include <stdio.h>
#include <unistd.h>

int main() {
  int i, ctr = 0;
  int cpid = fork();

  if (cpid == 0) {
    ctr = 100;
    for (i = 0; i < 3; i++)
      printf("Child counter = %d\n", ctr++);
  } else {
    for (i = 0; i < 3; i++)
      printf("Parent counter = %d\n", ctr++);
  }
  return 0;
}
