#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int cpid = fork();
  if (cpid == 0) {
    printf("Child Porcess\n");
  } else {
    printf("Parent Process\n");
  }
  return 0;
}
