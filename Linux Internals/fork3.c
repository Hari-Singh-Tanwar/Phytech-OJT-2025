#include <unistd.h>
#include <stdio.h>

int gvar = 555;
int main() {
  int lvar = 444;
  int cpid = fork();

  if(cpid == 0){
    printf("Child PID = %ld, gvar = %d, lvar = %d\n", (long)getpid(), gvar, lvar);
  }
  else{
    printf("Parent PID = %ld, gvar = %d, lvar = %d\n", (long)getpid(), gvar, lvar);
  }
  return 0;
}
