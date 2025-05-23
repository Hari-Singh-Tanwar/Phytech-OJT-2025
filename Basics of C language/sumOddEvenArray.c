#include <stdio.h>

int main() {
  int arr[10];
  int sumOdd = 0, sumEven = 0;
  printf("Enter 10 numbers\n");
  for (int i = 0; i < 10; i++) {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < 10; i++) {
    printf("%d ", arr[i]);

    if (arr[i] % 2 == 0) {
      sumEven += arr[i];
    } else {
      sumOdd += arr[i];
    }
  }
  printf("\n");

  printf("The sum of Even numbers are %d\n", sumEven);
  printf("The sum of Odd numbers are %d\n", sumOdd);
  return 0;
}
