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
  int arr[] = {34, 56, 27, 29, 23, 53, 16, 86, 34, 76};
  int length = sizeof(arr) / sizeof(int);
  for (int i = 0; i < length; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  bubbleSort(arr, length);
  for (int i = 0; i < length; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  printf("The second largest element in the array is %d and second smallest "
         "element in array is %d",
         arr[length - 2], arr[1]);

  return 0;
}
