#include <stdio.h>

int main() {
  int num1, num2;
  char operation;

  printf("Enter 1st number \n");
  scanf("%d", &num1);
  printf("Enter 2nd number\n");
  scanf("%d", &num2);

  printf("Enter operation to be done (Ex- +, -, *, /)\n");
  scanf(" %c", &operation);
  //srvoperation = getchar();

  switch (operation) {
  case '+':
    printf("%d + %d = %d\n", num1, num2, num1 + num2);
    break;

  case '-':
    printf(" %d - %d = %d\n", num1, num2, num1 - num2);
    break;

  case '*':
    printf("%d * %d = %d\n", num1, num2, num1 * num2);
    break;

  case '/':
    printf("%d / %d = %f\n", num1, num2, (float)num1 / num2);
    break;

  default:
    printf("Enver valid operation\n");
    break;
  }
  return 0;
}
