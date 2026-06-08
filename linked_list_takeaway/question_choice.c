#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"

void question_choice(){

     int32_t choice;
     printf("1. matrix creation\n");
     printf("2. insert a node to the beginning\n");
     printf("3. duplicate value\n");
     printf("4. resize matrix\n");
     printf("5. transpose\n");
     printf("\nenter your choice:\n");
     scanf("%d",&choice);
     matrix *M = NULL;
     switch(choice){
        case 1:
          creationTest();
          break;
        case 2:
          insertbeggingingTest();
          break;
        case 3:
           DuplicatevalueTest();
           break;
        case 4:
           resizeTest();
           break;
        case 5:
           transposeTest();
           break;
     }

}
