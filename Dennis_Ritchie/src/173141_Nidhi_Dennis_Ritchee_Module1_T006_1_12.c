/*
Author : Nidhi Goswami
Date: 11-02-2026
Description: Write a program that prints its input one word per line
*/

#include <stdio.h>
#include <stdint.h>
#include "module.h"

void  word_per_line(){
     int8_t Char;
     int8_t count=0;

     printf("enter string (press (CTRL + D) for exit):\n");
     while((Char = getchar()) != EOF){
         if(Char == ' ' || Char == '\t'){
            count += Char;
         }
         else{
            if(count>=9){
		putchar('\n');
                count=0;
            }
            putchar(Char);
         }
     }
}
