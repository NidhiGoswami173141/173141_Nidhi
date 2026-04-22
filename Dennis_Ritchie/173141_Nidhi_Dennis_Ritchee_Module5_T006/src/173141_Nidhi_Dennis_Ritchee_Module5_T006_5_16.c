/*
Author: Nidhi Goswami
Date : 7-04-2026
Description : Add the -d (``directory order'') option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with -f.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXLINES 5000
#define MAXLEN  1000

extern char *line_ptr[MAXLINES];
int32_t dircmp_only(char * , char *);
int32_t dircmp_fold(char *, char *);


int32_t is_char(char Char)
{

   return isalnum(Char) || Char == ' ';

}

int32_t dircmp(char *String1, char *String2 , int fold){

    char Char1 , Char2;
    while(1){
       while(*String1 && !is_char(*String1)){String1++;}
       while(*String2 && !is_char(*String2)){String2++;}

       Char1 = *String1;
       Char2 = *String2;

       if(fold){
          Char1 = tolower(Char1);
          Char2 = tolower(Char2);
       }
       if(Char1 != Char2){
           return Char1 - Char2;
       }
       if(Char1 == '\0'){
           return 0;
       }
       String1++;
       String2++;
    }

}

int32_t dircmp_only(char *String1 , char *String2){

    return dircmp(String1 , String2 , 0);

}

int32_t dircmp_fold(char *String1, char *String2){
     return dircmp(String1, String2 , 1);
}

void handle_flag_RNFD(int32_t argc , char *argv[]){

    int32_t nlines;
    int32_t numeric = 0 , reverse = 0 , fold = 0 , directory = 0 ;

    while(--argc > 0 && (*++argv)[0] == '-'){
        char *p = *argv;
        while(*++p){
           if(*p == 'n'){
              numeric = 1;
           }
           else if(*p == 'r'){
              reverse = 1;
           }
           else if(*p == 'f'){
              fold = 1;
           }
           else if(*p == 'd'){
              directory = 1;
           }
        }
    }
    printf("n=%d r=%d f=%d d=%d\n",numeric,reverse,fold,directory);

    int32_t (*comp_func)(void * , void *);

    if(numeric){
       comp_func = (int32_t (*)(void * , void *)) numcmp;
    }
    else if(directory && fold){
       comp_func = (int32_t (*)(void * , void *)) dircmp_fold;
    }
    else if(directory){
       comp_func = (int32_t (*)(void * , void *)) dircmp_only;
    }
    else if(fold){
        comp_func = (int32_t (*)(void * , void *)) strcmp_fold;
    }
    else{
         comp_func = (int32_t (*)(void * , void *))strcmp;
    }

    if((nlines = readlines_fun(line_ptr, MAXLINES))>=0){
        my_qsort_fun((void **)line_ptr, 0, nlines -1 , comp_func , reverse);
        writelines_fun(line_ptr,nlines);
    }
    else{
       printf("error: input too big for sorting\n");
    }
}
