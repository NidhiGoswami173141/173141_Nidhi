/*
Author: Nidhi Goswami
Date: 21-05-2026
Description: write a function to insert a node t as a left child of s in a threaded binary tree
*/

#include<stdio.h>
#include<stdint.h>
#include"../header/header.h"
#include<stdlib.h>

struct TBTNode
{
    int data;

    struct TBTNode* left;
    struct TBTNode* right;

    int lthread;
    int rthread;
};

struct TBTNode* createNode_fun(int value)
{
    struct TBTNode* newNode =(struct TBTNode*)malloc(sizeof(struct TBTNode));

    newNode->data = value;

    newNode->left = NULL;
    newNode->right = NULL;

    newNode->lthread = 1;
    newNode->rthread = 1;

    return newNode;
}

void insertLeft_fun(struct TBTNode* s,struct TBTNode* t)
{
    /*
    t's left thread becomes
    s's previous left
    */
    t->left = s->left;

    /*
    t's right thread points to s
    */
    t->right = s;

    /*
    Now s gets real left child
    */
    s->left = t;

    /*
    Left is now child, not thread
    */
    s->lthread = 0;
}

/* Inorder Traversal */
void inorder_tra(struct TBTNode* root)
{
    struct TBTNode* current = root;

    /* Move to leftmost node */
    while (current->lthread == 0)
        current = current->left;

    while (current != NULL)
    {
        printf("%d ", current->data);

        /*
        If right is thread
        */
        if (current->rthread == 1)
        {
            current = current->right;
        }
        else
        {
            /*
            Move to leftmost node
            in right subtree
            */
            current = current->right;

            while (current->lthread == 0)
                current = current->left;
        }
    }
}

void threadedTree_test()
{

    struct TBTNode* s = createNode_fun(10);

    struct TBTNode* t = createNode_fun(5);
    insertLeft_fun(s, t);

    printf("Inorder Traversal:\n");

    inorder_tra(t);
}
