/*
Author: Nidhi Goswami
Date: 20-05-2026
Description:  Perform Binary search, insertion and deletion using binary tree.
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

struct TreeNode* search(struct TreeNode* root, int key)
{
    if(root == NULL || root->data == key)
    {
        return root;
    }

    if(key < root->data)
    {
        return search(root->left, key);
    }

    return search(root->right, key);
}

struct TreeNode* minValueNode(struct TreeNode* node)
{
    struct TreeNode* current = node;

    while(current && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

struct TreeNode* deleteNode(struct TreeNode* root, int key)
{
    if(root == NULL)
    {
        return root;
    }

    if(key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }

    else if(key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }

    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        else if(root->left == NULL)
        {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }

        else if(root->right == NULL)
        {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp =
            minValueNode(root->right);

        root->data = temp->data;

        root->right =
            deleteNode(root->right, temp->data);
    }

    return root;
}

/*void BinarySearchTest()
{
    struct TreeNode* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder Traversal:\n");
    inorder(root);

    printf("\n");

    int key = 60;

    struct TreeNode* result = search(root, key);

    if(result != NULL)
    {
        printf("Found %d\n", key);
    }
    else
    {
        printf("Not Found\n");
    }

    root = deleteNode(root, 70);

    printf("\nAfter Deletion:\n");

    inorder(root);

    printf("\n");

}*/

void BinarySearchTest()
{
    struct TreeNode* root = NULL;

    int32_t nodes;

    printf("Enter number of nodes: ");

    scanf("%d", &nodes);

    printf("Enter %d elements:\n",nodes);

    for(int32_t index = 0;index < nodes;index++)
    {
        int32_t value;

        scanf("%d", &value);

        root = insert(root, value);
    }

    printf("\nInorder Traversal:\n");

    inorder(root);

    printf("\n");

    int32_t key;

    printf("\nEnter value to search: ");

    scanf("%d", &key);

    struct TreeNode* result = search(root, key);

    if(result != NULL)
    {
        printf("Found %d\n", key);
    }

    else
    {
        printf("Not Found\n");
    }

    int32_t deleteKey;

    printf("\nEnter value to delete: ");

    scanf("%d", &deleteKey);

    root = deleteNode(root,deleteKey);

    printf("\nAfter Deletion:\n");

    inorder(root);

    printf("\n");
}
