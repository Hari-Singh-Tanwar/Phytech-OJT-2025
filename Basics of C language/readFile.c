#include <stdio.h>

int main() {
  FILE *fp;
  char filename[100], ch;

  printf("Enter the file name to be read\n");
  scanf("%s", filename);

  fp = fopen(filename, "r");

  if (fp == NULL) {
    perror("Error opening File\n");
    return 1;
  }
  printf("Content of %s\n\n", filename);

  while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
  }
  fclose(fp);
  return 0;
}
