#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<header.h>
#include"../include/header.h"
void displayMatrix(matrix *M)
{
    int32_t row;
    int32_t column;

    node *temp;

    printf("\nMatrix:\n");

    for (row = 0; row < M->rows; row++)
    {
        temp = M->rowList[row];

        for (column = 0; column < M->columns; column++)
        {
            if (temp != NULL &&
                temp->column == column)
            {
                printf("%.0lf ", temp->value);

                temp = temp->rowPtr;
            }
            else
            {
                printf("0 ");
            }
        }

        printf("\n");
    }
}

node *createNode(int32_t row, int32_t column, double value)
{
    node *newNode = malloc(sizeof(node));

    if(newNode == NULL)
        return NULL;

    newNode->row = row;
    newNode->column = column;
    newNode->value = value;

    newNode->rowPtr = NULL;
    newNode->colPtr = NULL;

    return newNode;
}
void insertCopy(matrix *M,int row,int col,double value)
{
    node *newNode = createNode(row,col,value);

    insertAtBeginning(M,newNode);
}


void displayRowLinks(matrix *M)
{
    int i;

    printf("\nLinked List Representation\n");

    for(i = 0; i < M->rows; i++)
    {
        node *temp = M->rowList[i];

        printf("rowList[%d] -> ", i);

        while(temp)
        {
            printf("(%d,%d,%.0lf) -> ",
                    temp->row,
                    temp->column,
                    temp->value);

            temp = temp->rowPtr;
        }

        printf("NULL\n");
    }
}
