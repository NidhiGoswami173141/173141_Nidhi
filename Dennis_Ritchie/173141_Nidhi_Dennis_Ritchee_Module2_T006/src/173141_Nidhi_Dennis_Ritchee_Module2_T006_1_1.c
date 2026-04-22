/*
Author : Nidhi Goswami
Date : 19-02-2026
Description : Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing>
*/


#include<stdio.h>
#include<limits.h>

/*
Author : Nidhi Goswami
Date : 19-02-2026
Description : function for printing rangeof int,short , long
*/


void range_of_char_short_int_long(){
           printf("range of char , short , int , long (press (CYRL + D) for exit)\n");

           printf("signed Char : %d\n" , SCHAR_MIN);
           printf("signed Char : %d\n" , SCHAR_MAX);

           printf("unsigned Char : %u\n" , UCHAR_MAX);

           printf("signed short :%d\n" , SHRT_MIN);
           printf("signed short :%d\n" , SHRT_MAX);

           printf("unsigned short :%u\n" , USHRT_MAX);

           printf("signed int :%d\n",INT_MIN);
           printf("signed int :%d\n",INT_MAX);

           printf("unsigned int :%u\n",UINT_MAX);

           printf("signed long :%ld\n",LONG_MIN);
           printf("signed long :%ld\n",LONG_MAX);

           printf("unsigned long :%lu\n",ULONG_MAX);
}

