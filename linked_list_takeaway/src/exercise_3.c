/*
Author: Nidhi Goswami
Date: 1-06-2026
Description: Write a function int duplicatevalue(matrix* M, double value) that returns 1 if a  node with the value exists in the matrix. Return 0 if not.
*/

#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"
int32_t duplicatevalue(matrix *M, double value){
    int32_t index;
    for(index = 0; index < M->rows ; index++){
       node *temp = M-> rowList[index];
       while(temp){
           if(temp->value == value){
              return 1;
           }
           temp = temp -> rowPtr;
       }
    }
    return 0;
}

void DuplicatevalueTest()
{
    double searchValue;

    if(gMatrix == NULL)
    {
        printf("Create matrix first\n");
        return;
    }

    displayMatrix(gMatrix);

    printf("\nEnter value to search : ");
    scanf("%lf", &searchValue);

    if(duplicatevalue(gMatrix, searchValue))
        printf("Value %.2lf exists in matrix\n", searchValue);
    else
        printf("Value %.2lf does not exist in matrix\n", searchValue);
}
