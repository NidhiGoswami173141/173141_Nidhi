#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"../include/header.h"
void playingGame(){
int32_t choice;

do
{
    printf("\n===== SUPER 20 =====\n");
    printf("1. Load Questions File\n");
    printf("2. Play Game\n");
    printf("3. Display Tree\n");
    printf("4. Save Tree\n");
    printf("5. Exit\n");

    printf("Enter choice : ");
    scanf("%d",&choice);

    switch(choice)
    {
        QuestionNode *root = NULL;
        case 1:
           FILE *fp = fopen("questions.txt","r");

        if(fp == NULL)
        {
           printf("File not found\n");
           break;
        }

        root = buildTree(fp);

        fclose(fp);

        printf("Tree Loaded Successfully\n");

        break;

        case 2:
            printf("\nThink of an object...\n");
            printf("Possible categories include:\n");
            printf("- Animals\n");
            printf("- Vehicles\n");
            printf("- People\n");
            printf("\nAnswer all questions using y or n.\n");
            printf("If I don't know your object, I will learn it!\n\n");
            playGame(root);
            break;

        case 3:
            displayTree(root);
            break;

        case 4:
            saveTree(fp,root);
            printf("Tree Saved Successfully\n");
            break;

        case 5:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid Choice\n");
    }

}while(choice != 5);
}
