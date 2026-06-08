/*
Author: Nidhi Goswami
Date: 28-05-2026
Description:Suppose M is a matrix*, where matrix is as defined above. Write code to allocate enough space to initialize a matrix of n by m. 
*/

#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"
#include<stdlib.h>
matrix *gMatrix = NULL;
matrix *createMatrix(int32_t rows, int32_t columns)
{

   matrix *M = malloc(sizeof(matrix));
   if(M == NULL){
     return NULL;
   }
   M -> rows = rows;
   M-> columns = columns;

   M-> rowList = calloc(rows, sizeof(node *));
   M -> columnList = calloc(columns,sizeof(node *));

   if(M->rowList == NULL || M->columnList == NULL){
      free(M);
      return NULL;
   }
   return M;
}

void creationTest()
{
    int32_t rows, columns;

    printf("\nenter number of rows : ");
    scanf("%d", &rows);

    printf("\nenter number of columns : ");
    scanf("%d", &columns);

    gMatrix = createMatrix(rows, columns);

    if(gMatrix)
    {
        printf("\nmatrix allocated successfully\n");

        displayMatrix(gMatrix);
    }
}
