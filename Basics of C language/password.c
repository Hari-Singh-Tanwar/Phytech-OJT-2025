#include <stdbool.h>
#include <stdio.h>
int main() {

  const int password = 244466666;
  int input = 0;
  bool flag = false;
  do {
    printf("Input the Password:\n");
    scanf("%d", &input);
    if (password == input) {
      flag = true;
    } else {
      printf("Try again!!\n");
    }
  } while (flag == false);
  return 0;
}
