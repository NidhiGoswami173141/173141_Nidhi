/*
Author: Nidhi Goswami
Date: 26-05-2026
Description: Write a program to implement doubly link list as  a Circular Link List.
*/

#include<stdio.h>
#include<stdint.h>
#include"../header/header.h"
#include<stdlib.h>

void insertAtEnd_fun(struct dnode **head,int32_t number)
{
    struct dnode *newNode;
    struct dnode *lastNode;

    newNode = (struct dnode *)malloc(sizeof(struct dnode));

    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");

        return;
    }

    newNode->data = number;
    if(*head == NULL)
    {
        newNode->next = newNode;

        newNode->previous = newNode;

        *head = newNode;
    }
    else
    {
        lastNode = (*head)->previous;

        newNode->next = *head;

        newNode->previous = lastNode;

        lastNode->next = newNode;

        (*head)->previous = newNode;
    }
}


void insertAtBeginning_fun(struct dnode **head,int32_t number)
{
    struct dnode *newNode;
    struct dnode *lastNode;

    newNode = (struct dnode *)malloc(sizeof(struct dnode));

    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");

        return;
    }

    newNode->data = number;

    if(*head == NULL)
    {
        newNode->next = newNode;

        newNode->previous = newNode;

        *head = newNode;
    }
    else
    {
        lastNode = (*head)->previous;

        newNode->next = *head;

        newNode->previous = lastNode;

        lastNode->next = newNode;

        (*head)->previous = newNode;

        *head = newNode;
    }
}

void displayForward(struct dnode *head)
{
    struct dnode *currentNode;

    if(head == NULL)
    {
        printf("List is empty\n");

        return;
    }

    currentNode = head;

    printf("\nForward:\n");

    do
    {
        printf("%d <-> ",currentNode->data);

        currentNode = currentNode->next;

    }while(currentNode != head);

    printf("(HEAD)\n");
}

void displayBackward(struct dnode *head)
{
    struct dnode *currentNode;

    if(head == NULL)
    {
        printf("List is empty\n");

        return;
    }

    currentNode = head->previous;

    printf("\nBackward:\n");

    do
    {
        printf("%d <-> ",currentNode->data);

        currentNode = currentNode->previous;

    }while(currentNode != head->previous);

    printf("(TAIL)\n");
}

int32_t countNodes_fun(struct dnode *head)
{
    struct dnode *currentNode;

    int32_t count = 0;

    if(head == NULL)
    {
        return 0;
    }

    currentNode = head;

    do
    {
        count++;

        currentNode = currentNode->next;

    }while(currentNode != head);

    return count;
}

void Circular_Doubly_linked_list()
{
    struct dnode *head = NULL;

    insertAtEnd_fun(&head, 10);

    insertAtEnd_fun(&head, 20);

    insertAtEnd_fun(&head, 30);

    insertAtBeginning_fun(&head, 5);

    displayForward(head);

    displayBackward(head);

    printf("\nTotal Nodes = %d\n",countNodes_fun(head));

     d_delete(&head, 20);

    displayForward(head);

    printf("\nTotal Nodes = %d\n",countNodes_fun(head));

}
