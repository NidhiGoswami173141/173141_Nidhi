#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"

int main(){

    char choice;
    do{
       linkedlist_pq();
       getchar();
       printf("enter your choice do you want to continue or exit(Yes or No)\n");
       scanf("%c",&choice);
    }while (choice == 'y' || choice == 'Y');
    return 0;
}
