/*
Author: Nidhi Goswami
Date: 26-05-2026
Description: Write a C program to implement this Doubly Linked List (DLL).
*/

#include<stdio.h>
#include<stdlib.h>
#include"../header/header.h"
#include<stdint.h>

/*
add a new node at the end of the doubly linked list
*/
void d_append(struct dnode **head , int32_t number){
    struct dnode *currentNode;
    struct dnode *newNode;

    newNode = (struct dnode *)malloc(sizeof(struct dnode));

    if(newNode == NULL)
    {
        printf("memory allocation failed\n");
        return;
    }

    newNode->data = number;
    newNode->next = NULL;
    newNode->previous = NULL;

    if(*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        currentNode = *head;

        while(currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }

        currentNode->next = newNode;

        newNode->previous = currentNode;
    }
}

/*
add a new node at the beginning of the doubly linked list
*/
void d_addatbeg(struct dnode **head, int32_t number)
{
    struct dnode *newNode;
    struct dnode *firstNode;

    newNode = (struct dnode *)malloc(sizeof(struct dnode));

    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->data = number;

    newNode->previous = NULL;

    if(*head == NULL)
    {
        newNode->next = NULL;

        *head = newNode;
    }
    else
    {
        firstNode = *head;

        newNode->next = firstNode;

        firstNode->previous = newNode;

        *head = newNode;
    }
}

/*
adds a new node after the specified number of nodes
*/
void d_addafter(struct dnode *currentNode,int32_t location,int32_t number)
{

    if(currentNode == NULL)
    {
       printf("list is empty\n");
       return;
    }
    struct dnode *newNode;
    int32_t position;
    for(position = 0;position < location;position++)
    {
        currentNode = currentNode->next;

        if(currentNode == NULL)
        {
            printf("less than %d nodes present\n",location);

            return;
        }
    }
    newNode = (struct dnode *)malloc(sizeof(struct dnode));

    if(newNode == NULL)
    {
        printf("memory allocation failed\n");

        return;
    }

    newNode->data = number;

    newNode->next = currentNode->next;

    newNode->previous = currentNode;

    if(currentNode->next != NULL)
    {
        currentNode->next->previous = newNode;
    }

    currentNode->next = newNode;
}

/*
display the contents of the linked list
*/
void d_display(struct dnode* currentNode)
{
    if(currentNode == NULL)
    {
        printf("list is empty\n");

        return;
    }
    while(currentNode != NULL)
    {
        printf("%d <-> ", currentNode->data);

        currentNode = currentNode->next;
    }

    printf("NULL\n");
}

/*
counts the number of nodes present in the linked list
*/
int32_t d_count(struct dnode *currentNode)
{
    int32_t totalNodes = 0;

    while(currentNode != NULL)
    {
        totalNodes++;

        currentNode = currentNode->next;
    }

    return totalNodes;
}

/*
deletes the specified node from the doubly linked list
*/
void d_delete(struct dnode **head,int32_t number)
{
    struct dnode *currentNode;
    if(*head == NULL)
    {
        printf("list is empty\n");

        return;
    }

    currentNode = *head;
    while(currentNode != NULL)
    {
        if(currentNode->data == number)
        {
            if(currentNode->previous == NULL)
            {
                *head = currentNode->next;

                if(*head != NULL)
                {
                    (*head)->previous = NULL;
                }
            }
            else if(currentNode->next == NULL)
            {
                currentNode->previous->next = NULL;
            }
            else
            {
                currentNode->previous->next = currentNode->next;

                currentNode->next->previous = currentNode->previous;
            }

            free(currentNode);

            printf("%d deleted\n", number);

            return;
        }

        currentNode = currentNode->next;
    }

    printf("%d not found\n", number);
}
