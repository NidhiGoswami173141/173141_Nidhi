/*
Author: Nidhi Goswami
Date: 18-05-2026
Description: Perform  Post order , Pre order and in order traversal using array and link list for binary tree.
*/


#include<stdio.h>
#include"../header/header.h"
#include<stdint.h>
#include<stdlib.h>
#define SIZE 100
struct TreeNode
{
    int32_t data;
    struct TreeNode* left;
    struct TreeNode* right;
};
/*void linked_list_tree_traversal()
{
    struct TreeNode* root = createNode(10);

    root->left = createNode(20);
    root->right = createNode(30);

    root->left->left = createNode(40);
    root->left->right = createNode(50);

    printf("\nPreorder:\n");
    preorder(root);

    printf("\nInorder:\n");
    inorder(root);

    printf("\nPostorder:\n");
    postorder(root);

}*/

void linked_list_tree_traversal()
{
    int32_t size;

    printf("Enter number of nodes: ");
    scanf("%d", &size);

    int32_t arr[size];

    printf("Enter %d elements:\n", size);

    for (int32_t index = 0;index < size; index++)
    {
        scanf("%d", &arr[index]);
    }

    struct TreeNode* root =
        buildTree(arr, 0, size);

    printf("\nPreorder:\n");

    preorder(root);

    printf("\n\nInorder:\n");

    inorder(root);

    printf("\n\nPostorder:\n");

    postorder(root);

    printf("\n");
}


int64_t tree_arr[10] = {10,20,30,40,50};

void array_preorder(int32_t index, int32_t size)
{
    if (index >= size || tree_arr[index] == 0)
    {
        return;
    }

    printf("%d ", tree_arr[index]);

    array_preorder(2 * index + 1, size);

    array_preorder(2 * index + 2, size);
}

void array_inorder(int32_t index, int32_t size)
{
    if (index >= size || tree_arr[index] == 0)
    {
        return;
    }

    array_inorder(2 * index + 1, size);

    printf("%d ", tree_arr[index]);

    array_inorder(2 * index + 2, size);
}

void array_postorder(int32_t index, int32_t size)
{
    if (index >= size || tree_arr[index] == 0)
    {
        return;
    }

    array_postorder(2 * index + 1, size);

    array_postorder(2 * index + 2, size);

    printf("%d ", tree_arr[index]);
}

void array_tree_traversal()
{
    int size = 5;

    printf("Preorder:\n");
    array_preorder(0, size);

    printf("\nInorder:\n");
    array_inorder(0, size);

    printf("\nPostorder:\n");
    array_postorder(0, size);

}
