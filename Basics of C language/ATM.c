#include <stdatomic.h>
#include <stdio.h>

int main() {
  int Amount = 0;
  int tt = 0, fh = 0, h = 0, f = 0, t = 0, ten = 0, five = 0, two = 0, one = 0;
  printf("Enter the Amount\n");
  scanf("%d", &Amount);

  if (Amount >= 2000) {
    tt = Amount / 2000;
    Amount -= (tt * 2000);
  }
  if (Amount >= 500) {
    fh = Amount / 500;
    Amount -= (fh * 500);
  }
  if (Amount >= 100) {
    h = Amount / 100;
    Amount -= (h * 100);
  }
  if (Amount >= 50) {
    f = Amount / 50;
    Amount -= (f * 50);
  }
  if (Amount >= 20) {
    t = Amount / 20;
    Amount -= (t * 20);
  }
  if (Amount >= 10) {
    ten = Amount / 10;
    Amount -= (ten * 10);
  }
  if (Amount >= 5) {
    five = Amount / 5;
    Amount -= (five * 5);
  }
  if (Amount >= 2) {
    two = Amount / 2;
    Amount -= (two * 2);
  }
  if (Amount >= 1) {
    one -= Amount / 1;
  }
  if (Amount == 0) {
    printf("sucessfull calculated\n");
  }
  printf("There are:\n%d notes of 2000\n%d notes of 500\n%d notes of 100\n%d "
         "notes of 50\n%d notes of 20\n%d notes fo 10\n%d coins of 5\n%d coins "
         "of 2\n%d coins of 1\n",
         tt, fh, h, f, t, ten, five, two, one);
  return 0;
}
