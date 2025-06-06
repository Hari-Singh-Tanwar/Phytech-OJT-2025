#include <stdio.h>

int isPrime(int num) {
  if (num < 2) {
    return 0;
  }
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      return 0;
    }
  }
  return 1;
}

int main() {
  FILE *dataF, *evenF, *oddF, *primeF;
  int num;
  dataF = fopen("data.txt", "r");
  if (dataF == NULL) {
    perror("Error opening File\n");
    return 1;
  }
  evenF = fopen("even.txt", "w");
  oddF = fopen("odd.txt", "w");
  primeF = fopen("prime.txt", "w");
  if (evenF == NULL || oddF == NULL || primeF == NULL) {
    perror("Error opening output file\n");
    return 1;
  }
  while (fscanf(dataF, "%d", &num) != EOF) {
    if (num % 2 == 0) {
      fprintf(evenF, "%d\n", num);
    } else {
      fprintf(oddF, "%d\n", num);
    }

    if (isPrime(num)) {
      fprintf(primeF, "%d\n", num);
    }
  }

  fclose(dataF);
  fclose(evenF);
  fclose(oddF);
  fclose(primeF);

  printf("Sorting is done!!\n");
  return 0;
}
