#include <math.h>
#include <stdio.h>
int main() {
  double x1 = 25, y1 = 15;
  double x2 = 35, y2 = 10;
  double distance = 0;
  distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  printf("Distance between (%lf, %lf) and (%lf, %lf) is %lf\n ", x1, y1, x2, y2,
         distance);
  return 0;
}
