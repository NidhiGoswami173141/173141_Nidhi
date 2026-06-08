/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: Write a RemoveDuplicates() function which takes a list sorted in increasing order and deletes any duplicate nodes from the list. Ideally, the list should only be traversed once.
*/

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include"../header/header.h"

void RemoveDuplicates(struct node* head)
{
    struct node* current = head;

    struct node* duplicate;

    while(current != NULL && current->next != NULL)
    {
        if(current->data == current->next->data)
        {
            duplicate = current->next;

            current->next = duplicate->next;

            free(duplicate);
        }
        else
        {
            current = current->next;
        }
    }
}

void RemoveDuplicatesTest()
{
    struct node* head = NULL;

    Push(&head, 5);
    Push(&head, 5);
    Push(&head, 4);
    Push(&head, 3);
    Push(&head, 3);
    Push(&head, 2);
    Push(&head, 1);
    Push(&head, 1);

    printf("Before Remove:\n");

    Print(head);

    RemoveDuplicates(head);

    printf("After Remove:\n");

    Print(head);

    DeleteList(&head);
}
