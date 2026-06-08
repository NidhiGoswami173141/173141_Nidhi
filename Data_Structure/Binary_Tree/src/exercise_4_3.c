/*
Author: Nidhi Goswami
Date: 20-5-2026
Description: write a program to copy a binary search tree using recursion
*/

#include <stdio.h>
#include <stdlib.h>
#include"../header/header.h"
struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* copyTree(struct TreeNode* root)
{
    if (root == NULL)
        return NULL;

    struct TreeNode* newNode = createNode(root->data);

    newNode->left = copyTree(root->left);

    newNode->right = copyTree(root->right);

    return newNode;
}

void copyTree_test()
{
    struct TreeNode* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Original BST:\n");
    inorder(root);

    struct TreeNode* copiedTree = copyTree(root);

    printf("\n\nCopied BST:\n");
    inorder(copiedTree);
}
