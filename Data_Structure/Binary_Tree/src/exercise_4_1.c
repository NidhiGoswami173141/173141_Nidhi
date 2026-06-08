/*
Author: Nidhi Goswami
Date: 20-05-2026
Descritpion: write a program to travse a binary tree using preorder traversal method without using recursion
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include"../header/header.h"

struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

void preorder_fun(struct TreeNode* root)
{
    if (root == NULL)
        return;

    list* stack = NULL;

    push(&stack, root);

    while (stack != NULL)
    {
        struct TreeNode* current = pop(&stack);

        printf("%d ", current->data);

        if (current->right != NULL)
            push(&stack, current->right);

        if (current->left != NULL)
            push(&stack, current->left);
    }
}

void preorder_test()
{
    struct TreeNode* root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Preorder Traversal:\n");

    preorder_fun(root);
}
