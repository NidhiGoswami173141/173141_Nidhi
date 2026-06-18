#include<stdio.h>
#include<stdint.h>
#include"header.h"

void simpcat1(){

    char c;
    c = getchar();
    while(c != EOF){
       putchar(c);
       c = getchar();
    }
}
