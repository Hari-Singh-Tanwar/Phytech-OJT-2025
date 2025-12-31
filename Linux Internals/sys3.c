#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char cmd[50];
  int cpid;

  do {
    printf("Hari:- ");
    fgets(cmd, 50, stdin);
    system(cmd);
  } while (1);
  return 0;
}
