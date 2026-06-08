/*
Author: Nidhi Goswami
Date:20-5-2026
Description: write a program to travse a binary tree using postorder traversal method without using recursion
*/

#include<stdio.h>
#include<stdint.h>
#include"../header/header.h"
struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};
void postorder_fun(struct TreeNode* root)
{
    if (root == NULL)
        return;

    list* stack1 = NULL;
    list* stack2 = NULL;

    push(&stack1, root);

    while (stack1 != NULL)
    {
        struct TreeNode* current = pop(&stack1);

        push(&stack2, current);

        if (current->left != NULL)
            push(&stack1, current->left);

        if (current->right != NULL)
            push(&stack1, current->right);
    }

    while (stack2 != NULL)
    {
        struct TreeNode* current = pop(&stack2);

        printf("%d ", current->data);
    }
}

void postorder_test()
{
    struct TreeNode* root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("postorder Traversal:\n");

    postorder_fun(root);
}
