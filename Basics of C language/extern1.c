#include <stdio.h>

int shared_var = 100;

void display(void){
  printf("shared var %d\n", shared_var);
}

// int main(){
//   return 0;
// }