/*
Author      : Nidhi Goswami
Date        : 28-05-2026
Description : Insert node at beginning of  row list and column list
*/
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"../include/header.h"
void insertAtBeginning(matrix *M, node *ptr)
{

    int32_t r = ptr->row;
    int32_t c = ptr->column;

    ptr->rowPtr = M->rowList[r];
    M->rowList[r] = ptr;

   ptr->colPtr = M -> columnList[c];
   M -> columnList[c]=ptr;
}

void displayRowWise(matrix *M)
{
    int32_t row;
    node *temp;

    printf("\nRow Wise Traversal:\n");

    for (row = 0; row < M->rows; row++)
    {
        temp = M->rowList[row];

        printf("Row %d : ", row);

        while (temp != NULL)
        {
            printf("(%d,%d)=%.2lf  ", temp->row,temp->column,temp->value);

            temp = temp->rowPtr;
        }

        printf("\n");
    }
}

void displayColumnWise(matrix *M)
{
    int32_t column;
    node *temp;

    printf("\nColumn Wise Traversal:\n");

    for (column = 0; column < M->columns; column++)
    {
        temp = M->columnList[column];

        printf("Column %d : ", column);

        while (temp != NULL)
        {
            printf("(%d,%d)=%.2lf  ",temp->row, temp->column , temp->value);

            temp = temp->colPtr;
        }

        printf("\n");
    }
}

void insertbeggingingTest()
{
    int32_t row;
    int32_t column;
    double value;

    if(gMatrix == NULL)
    {
        printf("Create matrix first\n");
        return;
    }

    printf("\nEnter row index : ");
    scanf("%d", &row);

    printf("Enter column index : ");
    scanf("%d", &column);

    printf("Enter value : ");
    scanf("%lf", &value);
    if(row < 0 || row >= gMatrix->rows ||  column < 0 || column >= gMatrix->columns)
    {
        printf("Invalid Index\n");
        return;
    }
    insertAtBeginning(gMatrix,createNode(row,column,value));
    displayRowWise(gMatrix);
    displayColumnWise(gMatrix);
    displayMatrix(gMatrix);
    displayRowLinks(gMatrix);
}
