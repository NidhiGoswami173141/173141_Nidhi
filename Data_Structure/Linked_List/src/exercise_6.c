/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: Write a SortedInsert() function which given a list that is sorted in increasing order, and a single node, inserts the node into the correct sorted position in the list. While Push() allocates a new node to add to the list, SortedInsert() takes an existing node, and just rearranges pointers to insert it into the list.
*/


#include<stdio.h>
#include"../header/header.h"
#include<stdint.h>
#include<stdlib.h>

void SortedInsert(struct node** headRef, struct node* newNode)
{
    struct node* current = *headRef;

    if(*headRef == NULL || newNode->data < current->data)
    {
        newNode->next = *headRef;

        *headRef = newNode;

        return;
    }

    while(current->next != NULL &&
          current->next->data < newNode->data)
    {
        current = current->next;
    }

    newNode->next = current->next;

    current->next = newNode;
}

void SortedInsertTest()
{
    struct node* head = NULL;

    struct node* newNode;

    Push(&head, 40);
    Push(&head, 20);
    Push(&head, 10);

    newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = 30;

    newNode->next = NULL;

    Print(head);

    SortedInsert(&head, newNode);

    Print(head);
}
