#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t cpid = fork();

  if (cpid == 0) {
    printf("Running child, PID=%ld PPID=%ld\n", (long)getpid(),
           (long)getppid());
    while (1)
      ;
  } else {
    printf("Terminating parent, PID=%ld PPID=%ld\n", (long)getpid(),
           (long)getppid());
    exit(0);
  }
  return 0;
}
