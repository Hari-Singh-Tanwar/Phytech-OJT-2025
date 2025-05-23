#include <stdio.h>

int main() {
  int arr[10];
  int sum = 0;

  // Tiking
  printf("Enter 10 integers\n");
  for (int i = 0; i < 10; i++) {
    scanf("%d ", &arr[i]);
  }

  // Printing Array
  printf("Entered array is\n");
  for (int i = 0; i < 10; i++) {
    printf("%d ", arr[i]);
    sum += arr[i];
  }
  printf("\n");
  printf("The entered sum is %d\n", sum);
  return 0;
}
