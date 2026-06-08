#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"

int main(){
    char choice;
    do
    {
        playingGame();
        getchar();
        printf("\nDo you want to continue or exit?(yes or no)");
        scanf("%c", &choice);


    } while (choice == 'y' || choice == 'Y');

}
