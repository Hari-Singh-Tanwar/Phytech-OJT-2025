#include <math.h>
#include <stdio.h>

int main() {

  float P, r, n, t;
  printf("Enter the principle amount \n");
  scanf("%f", &P);
  printf("Enter the Intrest Rate\n");
  scanf("%f", &r);
  printf("Enter the time in years\n");
  scanf("%f", &t);
  printf("Enter the number of times the intrest is compunded per year\n");
  scanf("%f", &n);

  float A = 0;
  A = P * pow((1 + (r / n)), t);
  printf("The calculated amount = %f", A);
  return 0;
}
