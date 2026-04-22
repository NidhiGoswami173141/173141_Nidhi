/*
Author: Nidhi Goswami
Date : 9-3-2026
Description: Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#define swap(t,x,y){t=x;x=y;y=t;}


/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for  swap two arguments of type t define macro
*/

void swap_arguments(){
     int32_t choice;

     printf("enter you choice for input 1)integers 2)char 3)float\n");
     scanf("%d",&choice);
     if(choice==1){
     int32_t t;
     int32_t x;
     int32_t y;
     printf("enter first int argument x:\n");
     scanf("%d",&x);
     printf("enter second int argument y:\n");
     scanf("%d",&y);

     swap(t,x,y);

     printf("x:  %d\n",x);
     printf("y:  %d\n",y);
     }
     else if(choice==2){
     char t;
     char x;
     char y;
     printf("enter first argument x:\n");
     scanf("  %c",&x);
     printf("enter second argument y:\n");
     scanf("  %c",&y);

     swap(t,x,y);

     printf("x:  %c\n",x);
     printf("y:  %c\n",y);
     }
     else if(choice == 3){
     float t;
     float x;
     float y;
     printf("enter first argument x:\n");
     scanf("%f",&x);
     printf("enter second argument y:\n");
     scanf("%f",&y);

     swap(t,x,y);

     printf("x:  %f\n",x);
     printf("y:  %f\n",y);
     }
     else{
     printf("invalid");
     }
}
