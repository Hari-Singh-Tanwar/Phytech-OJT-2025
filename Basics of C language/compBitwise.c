#include <stdio.h>

int main()
{
  int a = 10, b = 15;
  int comp  = 0;
  comp = a ^ b;
 
  if(comp){
    printf("Ther numbers are not equal\n");
    
  }
  else {
    printf("The numbers are equal\n");
  }
  return 0;
}
