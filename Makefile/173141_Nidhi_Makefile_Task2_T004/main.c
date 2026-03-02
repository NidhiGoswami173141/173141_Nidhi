//#################################################################################
//Author: Nidhi Goswami
//Date : 5-2-2026
//Description: main fucntion in this and function call from src1 , src2 , and src3
//#################################################################################

#include<stdio.h>
int main(){
  void function1();
  void function2();
  void function3();
  int funct;
  printf("1 2 3 :");
  if (scanf("%d", &funct) == 0){
	printf("Failed to take user input\n");
	return 0;
  }
  switch(funct){
  case 1:
      function1();
      break;
  case 2:
      function2();
      break;
  case 3:
      function3();
      break;
  };
  return 0;
}
