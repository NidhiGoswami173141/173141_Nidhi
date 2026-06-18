#include<stdio.h>
#include"header.h"
void simpcat2(){

    char c;
    int i;
    i= read(0,&c,1);
    while(i>0){
       write(1,&c,1);
       i = read(0,&c,1);
    }
}
