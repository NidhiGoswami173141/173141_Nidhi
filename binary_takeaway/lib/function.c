#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"

QuestionNode *createNode(char *data)
{
    QuestionNode *newNode = malloc(sizeof(QuestionNode));

    strcpy(newNode->data, data);
    newNode->yes = NULL;
    newNode->no = NULL;

    return newNode;
}

void removePrefix(char *str)
{
    memmove(str, str + 2, strlen(str + 2) + 1);
}

QuestionNode *buildTree(FILE *fp)
{
    char line[200];

    if (fgets(line, sizeof(line), fp) == NULL)
        return NULL;

    line[strcspn(line, "\n")] = '\0';

    QuestionNode *root = createNode(line + 2);

    if (line[0] == 'Q')
    {
        root->yes = buildTree(fp);
        root->no = buildTree(fp);
    }

    return root;
}

char getYesNo()
{
    char ans[20];

    scanf("%19s", ans);

    if (tolower(ans[0]) == 'y')
        return 'y';

    if (tolower(ans[0]) == 'n')
        return 'n';

    printf("Please answer yes or no: ");
    return getYesNo();
}


void learn(QuestionNode *node)
{
    char object[200];
    char question[200];
    char answer;

    printf("Drat, I lost.\n");

    printf("What was your object? ");
    scanf(" %[^\n]", object);

    printf("Type a Y/N question to distinguish %s from %s:\n",
           object,
           node->data);

    scanf(" %[^\n]", question);

    printf("And what is the answer for %s? ", object);

    answer = getYesNo();

    QuestionNode *oldAnswer = createNode(node->data);
    QuestionNode *newAnswer = createNode(object);

    strcpy(node->data, question);

    if (answer == 'y')
    {
        node->yes = newAnswer;
        node->no = oldAnswer;
    }
    else
    {
        node->yes = oldAnswer;
        node->no = newAnswer;
    }
}



void displayTree(QuestionNode *root)
{
    if(root == NULL)
        return;

    if(root->yes == NULL && root->no == NULL)
    {
        printf("A: %s\n", root->data);
        return;
    }

    printf("Q: %s\n", root->data);

    displayTree(root->yes);
    displayTree(root->no);
}
