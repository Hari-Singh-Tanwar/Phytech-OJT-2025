#include <stdio.h>

int main() {
  float Ph, ch, bio, math, comp, Per = 0;
  printf("Enter the marks of Physics, Chemistry, Biology, Mathematics and Computer\n");
  scanf("%f %f %f %f %f", &Ph, &ch, &bio, &math, &comp);

  Per = (Ph + ch + bio + math + comp) / 5;
  printf("Percentage = %f\n", Per);

  if (Per >= 90) {
    printf("Grade A\n");
  } else if (Per >= 80) {
    printf("Grade B\n");
  } else if (Per >= 70) {
    printf("Grade C\n");
  } else if (Per >= 60) {
    printf("Grade D\n");
  } else if (Per >= 40) {
    printf("Grade E\n");
  } else if (Per < 40) {
    printf("Fail\n");
  }
  return 0;
}
