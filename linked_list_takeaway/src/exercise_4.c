/*
Author: Nidhi Goswami
Date: 31-5-2026
Description:Write a function int resize(matrix**) that doubles the rows and columns of the matrix. The old nodes need to be copied to the new matrix. Return 0 if success, 1 
if failure.*/

#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"
#include<stdlib.h>

int32_t resize(matrix **M){
   matrix *old = *M;
   matrix *newMatrix = createMatrix(old->rows *2 , old->columns*2);
   if(newMatrix== NULL){
     return 1;
   }
   int32_t index;
   for(index = 0; index < old->rows;index++){
      node *temp = old-> rowList[index];
      while(temp){
          insertCopy(newMatrix, temp->row , temp->column , temp -> value);
          temp = temp->rowPtr;
      }
   }
   *M = newMatrix;
   return 0;
}

void resizeTest()
{
    if(gMatrix == NULL)
    {
        printf("Create matrix first\n");
        return;
    }

    printf("\nBefore Resize\n");

    displayMatrix(gMatrix);

    printf("\nMatrix Size : %d x %d\n",gMatrix->rows,gMatrix->columns);

    if(resize(&gMatrix) == 0)
    {
        printf("\nResize Successful\n");
    }

    printf("\nAfter Resize\n");

    displayMatrix(gMatrix);

    printf("\nNew Matrix Size : %d x %d\n",gMatrix->rows,gMatrix->columns);
}
