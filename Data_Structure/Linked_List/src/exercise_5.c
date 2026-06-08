/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: Function InsertNth() which can insert a new node at any index within a list. Push() is similar, but can only insert a node at the head end of the list (index 0). The caller may specify any index in the range [0..length], and the new node should be inserted so as to be at that index.
*/

#include<stdio.h>
#include<stdint.h>
#include "../header/header.h"

void InsertNth(struct node** headRef, int index, int data)
{
    struct node* current;

    int count = 0;

    if(index == 0)
    {
        Push(headRef, data);

        return;
    }

    current = *headRef;

    while(count < index - 1)
    {
        current = current->next;

        count++;
    }

    Push(&(current->next), data);
}

void InsertNthTest()
{
    struct node* head = NULL;

    InsertNth(&head, 0, 13);

    InsertNth(&head, 1, 42);

    InsertNth(&head, 1, 5);
    InsertNth(&head, 0, 5);

    Print(head);

    DeleteList(&head);
}
