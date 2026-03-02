/*
Author : Nidhi Goswami
Date : 23-02-2026
Description : Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"

void lowercase(){
      char Char;
      printf("enter a string(press (CTRL + D) for exit): \n");
      while((Char = getchar()) != EOF){
      Char = (Char >= 'A' && Char <= 'Z') ? (Char + 'a' - 'A') : Char;
      printf("%c",Char);
      }
}
