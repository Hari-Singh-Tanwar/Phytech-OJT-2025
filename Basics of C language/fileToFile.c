#include <stdio.h>

int main() {
  FILE *f_source, *f_destination;
  char ch;

  f_source = fopen("File1.txt", "r");

  if (f_source == NULL) {
    printf("Error opening source file\n");
    return 1;
  }

  f_destination = fopen("data.txt", "w");

  if (f_destination == NULL) {
    printf("Error opening destination file\n");
    return 1;
  }

  while ((ch = fgetc(f_source)) != EOF) {
    fputc(ch, f_destination);
  }

  printf("File copied successfully/n");

  fclose(f_source);

  fclose(f_destination);

  return 0;
}
