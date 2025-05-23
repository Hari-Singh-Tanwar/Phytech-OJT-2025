#include <stdio.h>

int main(){
  int arr[5];

  printf("Eneter 5 integer\n");
  for(int i = 0; i < 5; i++){
    scanf("%d", &arr[i]);
  }
  printf("Prining only Odd elements\n");
  for(int i = 0; i<5;i++){
    if(arr[i]%2 != 0){
      printf("%d ",arr[i]);
    }
  }
  printf("\n");
  return 0;
}
