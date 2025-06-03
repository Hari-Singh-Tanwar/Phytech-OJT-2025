#include <stdio.h>

int main() {
  FILE *f;
  char input[100];
  f = fopen("File1.txt", "w");
  if (f == NULL) {
    printf("Error");
    return 1;
  }
  printf("Enter your name \n");
  fgets(input, sizeof(input), stdin);
  fputs(input, f);
  printf("data written to the file \n");
  fclose(f);
  return 0;
}
