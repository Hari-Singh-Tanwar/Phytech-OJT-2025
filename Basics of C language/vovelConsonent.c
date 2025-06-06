#include <stdio.h>

int main() {
  FILE *file;
  char ch;
  int vowels = 0, consonants = 0;

  file = fopen("word.txt", "r");

  if (file == NULL) {
    perror("Error opening file");
    return 0;
  }

  while ((ch = fgetc(file)) != EOF) {
    if (ch >= 'a' && ch <= 'z') {
      if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
        vowels++;
      } else {
        consonants++;
      }
    }
  }

  fclose(file);
  printf("vowles = %d and consonants = %d", vowels, consonants);
  return 0;
}
