#include <stdio.h>

int main() {

  FILE *f;
  char ch;
  int count = 0;

  f = fopen("data.txt", "r");
  if (f == NULL) {
    perror("Error opeing FIle");
    return 1;
  }

  while ((ch = fgetc(f)) != EOF) {
    count++;
  }

  fclose(f);

  printf("Total number of character in data.txt is %d\n", count);
  return 0;
}
