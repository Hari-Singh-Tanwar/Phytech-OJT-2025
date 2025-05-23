#include <stdio.h>

int main() {
  int arr[10];
  int sumFirst5 = 0, sumSecond5 = 0;
  printf("Enter the 10 integer\n");

  // Taking inputs form users
  for (int i = 0; i < 10; ++i) {
    
    scanf("%d", &arr[i]);
  }
  // Printing the array
  for (int i = 0; i < 10; ++i) {
    printf("%d, ", arr[i]);
    if (i < 5) {
      sumFirst5 += arr[i];
    } else {
      sumSecond5 += arr[i];
    }
  }
  printf("\n");

  printf("The sum of first 5 elements = %d\n", sumFirst5);
  printf("The sum of last 5 elements = %d\n", sumSecond5);

  if (sumFirst5 == sumSecond5) {
    printf("The Sum of first 5 elements is equal to last 5 elements\n");
  } else {
    printf(
        "The sum of first 5 elements is not equal to the second 5 elements\n");
  }

  return 0;
}
