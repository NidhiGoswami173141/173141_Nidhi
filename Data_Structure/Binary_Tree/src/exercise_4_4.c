/*
Author: Nidhi Goswami
Date: 20-5-2026
Description: write a program to compare two binary search trees using recursion
*/

#include<stdio.h>
#include<stdint.h>
#include"../header/header.h"
#include <stdlib.h>
#include <stdbool.h>
struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

bool compareTrees(struct TreeNode* root1,
                  struct TreeNode* root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    if (root1->data != root2->data)
        return false;

    return compareTrees(root1->left, root2->left) && compareTrees(root1->right, root2->right);
}

void compareTree_test()
{
    struct TreeNode* root1 = NULL;
    struct TreeNode* root2 = NULL;

    root1 = insert(root1, 50);
    root1 = insert(root1, 30);
    root1 = insert(root1, 70);
    root1 = insert(root1, 20);
    root1 = insert(root1, 40);

    root2 = insert(root2, 50);
    root2 = insert(root2, 30);
    root2 = insert(root2, 70);
    root2 = insert(root2, 100);
    root2 = insert(root2, 40);

    printf("First BST:\n");
    inorder(root1);

    printf("\n\nSecond BST:\n");
    inorder(root2);


    if (compareTrees(root1, root2))
        printf("\n\nBoth BSTs are Equal\n");

    else
        printf("\n\nBoth BSTs are NOT Equal\n");
}
