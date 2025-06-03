#include <stdio.h>

void PrintMatrix(int a[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d\t", a[i][j]);
    }
    printf("\n");
  }
}

void TransposeMatrix(int a[3][3], int b[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      b[j][i] = a[i][j];
    }
  }
}

int main() {
  int matrix1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  int matrix2[3][3];

  printf("\nOriginal matrix \n");

  PrintMatrix(matrix1);

  TransposeMatrix(matrix1, matrix2);

  printf("\n\nTrasposed matrix \n");

  PrintMatrix(matrix2);

  return 0;
}
