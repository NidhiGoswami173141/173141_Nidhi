/*
Author: Nidhi Goswami
Date: 11-02-2026
Description: functions for count blanks, tabs, and newlines.
*/

#include <stdio.h>
#include <stdint.h>
#include "module.h"

void count_blank_tabs_newline()
{
   int8_t Char;
   int8_t  tabs = 0;
   int8_t blank =0;
   int8_t newline =0;


   printf("enter text:\n");
   while((Char = getchar()) != EOF){
      if(Char == '\t'){
        tabs++;
      }
      else if(Char == ' '){
        blank++;
      }
      else if(Char == '\n'){
        newline++;
      }
      else{
         continue;
      }
   }
   printf("\nBlanks are %d\nTabs are %d\nNew Lines are %d\n", blank, tabs, newline-1);
}
