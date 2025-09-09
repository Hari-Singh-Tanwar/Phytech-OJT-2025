#include <stdio.h>

int main() {
  int a, b, response;
  float result = 0;
  char buffer[10], op;

  FILE *data = fopen("data.txt", "r");
  if (data == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  fscanf(data, "%d %d", &a, &b);
  // printf("Recive variables : %d and %d\n", a, b);

  fclose(data);

again:
  printf("a = %d, b = %d\n", a, b);
  printf("Enter the operation you want to perform\n1: add\n2: subtract\n3: "
         "multiply\n4: div\n5: mod\n");
  scanf("%d", &response);

  switch (response) {
  case 1:
    result = a + b;
    op = '+';
    printf("%d + %d = %0.2f\n", a, b, result);
    break;

  case 2:
    result = a - b;
    op = '-';
    printf("%d - %d = %0.2f\n", a, b, result);
    break;

  case 3:
    result = a * b;
    op = 'x';
    printf("%d x %d = %0.2f\n", a, b, result);
    break;

  case 4:
    result = (float)a / b;
    op = '/';
    printf("%d / %d = %f", a, b, result);
    break;

  case 5:
    result = a % b;
    op = '%';
    printf("%d %% %d = %0.2f\n", a, b, result);
    break;

  default:
    printf("Enter valid operation\n");
    goto again; // looping when getting wrong input
    break;
  }

  FILE *result_data = fopen("result.txt", "w"); // writing to the data file

  if (result_data == NULL) {
    printf("Error opening result_data.txt");
    return 1;
  }
  
  fprintf(result_data, "%d %c %d = %0.2f", a, op, b, result);

  fclose(result_data);

  return 0;
}
