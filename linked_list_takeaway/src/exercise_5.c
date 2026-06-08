/*
Author: Nidhi Goswami
Date: 31-05-2026
Description: Write a function int transpose(matrix**) that takes the transpose of the matrix. Transpose of a matrix M is defined as a matrix M1 where rows of M are equivalent to columns of M1 and columns of M are equivalent to rows of M1. For example the transpose of M = {{1,2},{3,4}} is M1 = {{1,3},{2,4}}.
*/
#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"
int32_t transpose(matrix **M){
   matrix *old = *M;
   matrix *newMatrix = createMatrix(old->columns, old ->rows);
   if(newMatrix == NULL){
      return 1;
   }
   int32_t index;
   for(index = 0; index <old->rows ; index++){
      node *temp = old -> rowList[index];
      while(temp){
        insertCopy(newMatrix, temp -> column, temp -> row, temp -> value);
        temp = temp -> rowPtr;
      }
   }
   *M = newMatrix;
   return 0;
}


void transposeTest()
{
    if(gMatrix == NULL)
    {
        printf("Create matrix first\n");
        return;
    }

    printf("\nBefore Transpose\n");

    displayMatrix(gMatrix);

    printf("\nMatrix Size : %d x %d\n",gMatrix->rows,gMatrix->columns);

    if(transpose(&gMatrix) == 0)
    {
        printf("\nTranspose Successful\n");
    }

    printf("\nAfter Transpose\n");

    displayMatrix(gMatrix);

    printf("\nNew Matrix Size : %d x %d\n", gMatrix->rows, gMatrix->columns);
}
