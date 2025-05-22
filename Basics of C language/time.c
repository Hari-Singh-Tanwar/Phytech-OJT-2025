#include <stdio.h>

int main() {
  int time;
  int hr, min, sec;

  printf("Enter Time in seconds\n");
  scanf("%d", &time);

  hr = time / 3600;
  min = (time - (3600 * hr))  / 60;
  sec = time - (3600 * hr) - (60 * min);

  printf("hr:min:sec = %d:%d:%d\n", hr, min, sec);
  return 0;
}
