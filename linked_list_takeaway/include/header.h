#ifndef HEADER_H
#define HEADER_H
#include<stdio.h>
#include<stdint.h>
typedef struct node{
    int32_t row, column;
    double value;
    struct node* rowPtr;
    struct node* colPtr;
}node;

typedef struct matrix{
   node** rowList;
   node** columnList;
   int32_t rows, columns;
}matrix;
extern matrix *gMatrix;
void creationTest();
matrix *createMatrix(int32_t rows, int32_t columns);
void insertbeggingingTest();
void displayMatrix(matrix *M);
node *createNode(int32_t row, int32_t column,double value);
int32_t duplicatevalue(matrix *M, double value);
int32_t resize(matrix **M);
int32_t transpose(matrix **M);
void insertCopy(matrix *M,int row,int col,double value);
void insertAtBeginning(matrix *M, node *ptr);
void DuplicatevalueTest();
void resizeTest();
void transposeTest();
void displayRowLinks(matrix *M);
#endif
