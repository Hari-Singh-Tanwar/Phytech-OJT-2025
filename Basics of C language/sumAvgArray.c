#include <stdio.h>

void bubbleSort(int arr[], int length) {
  int swap;
  for (int i = 0; i < length - 1; i++) {
    for (int j = 0; j < length - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = swap;
      }
    }
  }
}

int main() {

  int arr[8];
  int sum = 0, length;
  float avg = 0;
  printf("Enter the 8 integers\n");
  for (int i = 0; i < 8; i++) {
    scanf("%d", &arr[i]);
  }
  printf("\n");
  length = sizeof(arr) / sizeof(int);
  bubbleSort(arr, length);
  printf("The entered sorted array is\n");

  for (int i = 0; i < 8; i++) {
    printf("%d ", arr[i]);
    sum += arr[i];
  }
  avg = sum / 8.0;
  printf("\nThe sum of array is %d\nThe average of array is %f\n", sum, avg);
  printf("The lagest number is %d, and the smallest number is %d\n", arr[7],
         arr[0]);
  return 0;
}
