/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: Write an InsertSort() function which given a list, rearranges its nodes so they are sorted in increasing order. It should use SortedInsert().
*/


#include<stdio.h>
#include"../header/header.h"
#include<stdlib.h>
#include<stdint.h>


void InsertSort(struct node** headRef)
{
    struct node* current = *headRef;

    struct node* next;

    struct node* sorted = NULL;

    while(current != NULL)
    {
        next = current->next;

        SortedInsert(&sorted, current);

        current = next;
    }

    *headRef = sorted;
}

void InsertSortTest()
{
    struct node* head = NULL;

    Push(&head, 2);
    Push(&head, 5);
    Push(&head, 1);
    Push(&head, 3);

    printf("before Sort:\n");

    Print(head);

    InsertSort(&head);

    printf("after Sort:\n");

    Print(head);

    DeleteList(&head);
}
