#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct QuestionNode
{
    char data[200];

    struct QuestionNode *yes;
    struct QuestionNode *no;

} QuestionNode;

QuestionNode *createNode(char *data);

void removePrefix(char *str);

QuestionNode *buildTree(FILE *fp);

char getYesNo(void);

void learn(QuestionNode *node);

void playGame(QuestionNode *root);

void saveTree(FILE *fp, QuestionNode *root);

void freeTree(QuestionNode *root);
void displayTree(QuestionNode *root);
#endif
