/*
Author: Nidhi Goswami
Date: 18-05-2026
Description: Implement Tree with Arrays & Link list.
*/

#include<stdio.h>
#include"../header/header.h"
#include<stdint.h>
#include<stdlib.h>
#define SIZE 100
int64_t tree_array[SIZE];
struct TreeNode
{
    int32_t data;
    struct TreeNode* left;
    struct TreeNode* right;
};
void insertRoot(int64_t value)
{
    tree_array[0] = value;
}

void insertLeft(int64_t parentIndex, int64_t value)
{
    int32_t left = 2 * parentIndex + 1;

    tree_array[left] = value;
}

void insertRight(int64_t parentIndex, int64_t value)
{
    int64_t right = 2 * parentIndex + 2;

    tree_array[right] = value;
}

void display_tree()
{
    for (int32_t index = 0; index < 10; index++)
    {
        if (tree_array[index] != 0)
        {
            printf("index %d : %d\n", index, tree_array[index]);
        }
    }
}

/*void Array_tree_implementaation()
{
    insertRoot(10);

    insertLeft(0, 20);
    insertRight(0, 30);

    insertLeft(1, 70);
    insertRight(1, 50);

    display_tree();

}*/
void Array_tree_implementaation()
{
    int32_t nodes;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter %d elements:\n", nodes);

    for (int32_t index = 0; index < nodes; index++)
    {
        scanf("%ld", &tree_array[index]);
    }

    printf("\nArray Representation:\n");

    for (int32_t index = 0; index < nodes; index++)
    {
        printf("Index %d : %ld\n",
               index,
               tree_array[index]);
    }
}

/*void linked_list_tree_implementation()
{
    struct TreeNode* root = createNode(10);

    root->left = createNode(20);
    root->right = createNode(30);

    root->left->left = createNode(40);
    root->left->right = createNode(50);

    printf("Inorder Traversal:\n");

    inorder(root);

    return 0;
}*/
/*struct TreeNode* buildTree(int32_t arr[],
                           int32_t index,
                           int32_t nodes)
{
    if (index >= nodes)
    {
        return NULL;
    }

    struct TreeNode* root =
        createNode(arr[index]);

    root->left =
        buildTree(arr,
                  2 * index + 1,
                  nodes);

    root->right =
        buildTree(arr,
                  2 * index + 2,
                  nodes);

    return root;
}*/
void linked_list_tree_implementation()
{
    int32_t nodes;

    printf("\nEnter number of nodes: ");
    scanf("%d", &nodes);

    int32_t arr[nodes];

    printf("Enter %d elements:\n", nodes);

    for (int32_t index = 0; index < nodes; index++)
    {
        scanf("%d", &arr[index]);
    }

    struct TreeNode* root =
        buildTree(arr, 0, nodes);

    printf("\nInorder Traversal:\n");

    inorder(root);

    printf("\n");
}
