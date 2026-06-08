#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"

void playGame(QuestionNode *root)
{
    if (root == NULL)
        return;

    if (root->yes == NULL && root->no == NULL)
    {
        printf("Are you thinking of: %s? ", root->data);

        if (getYesNo() == 'y')
        {
            printf("Hey, I win!\n");
        }
        else
        {
            learn(root);
        }

        return;
    }

    printf("%s ", root->data);

    if (getYesNo() == 'y')
        playGame(root->yes);
    else
        playGame(root->no);
}



void saveTree(FILE *fp, QuestionNode *root)
{
    if (root == NULL)
        return;

    if (root->yes == NULL && root->no == NULL)
    {
        fprintf(fp, "A:%s\n", root->data);
        return;
    }

    fprintf(fp, "Q:%s\n", root->data);

    saveTree(fp, root->yes);
    saveTree(fp, root->no);
}
