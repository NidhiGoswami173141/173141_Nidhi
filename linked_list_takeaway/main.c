#include<stdio.h>
#include<stdlib.h>
#include"../include/header.h"

int main(){
   char choice;

    do
    {
        question_choice();
        getchar();
        printf("\nDo you want to continue or exit?(yes or no)");
        scanf(" %c", &choice);


    } while (choice == 'y' || choice == 'Y');
    return 0;

}
