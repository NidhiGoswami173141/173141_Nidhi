/*
Author:Nidhi Goswami
Date: 13-05-2026
Description: Write an Append() function that takes two lists, 'a' and 'b', appends 'b' onto the end of 'a', and then sets 'b' to NULL (since it is now trailing off the end of 'a'). Here is a drawing of a sample call to Append(a, b) with the start state in gray and the end state in black. At the end of the call, the 'a' list is {1, 2, 3, 4}, and 'b' list is empty.
*/

#include<stdio.h>
#include"../header/header.h"
#include<stdlib.h>
#include<stdint.h>
void Append(struct node** aRef, struct node** bRef)
{
    struct node* current;

    if(*aRef == NULL)
    {
        *aRef = *bRef;
    }
    else
    {
        current = *aRef;

        while(current->next != NULL)
        {
            current = current->next;
        }

        current->next = *bRef;
    }

    *bRef = NULL;
}

void AppendTest()
{
    struct node* a = NULL;

    struct node* b = NULL;

    Push(&a, 2);
    Push(&a, 1);

    Push(&b, 4);
    Push(&b, 3);

    printf("list A before:\n");

    Print(a);

    printf("list B before:\n");

    Print(b);

    Append(&a, &b);

    printf("list A after:\n");

    Print(a);

    printf("list B after:\n");

    Print(b);

    DeleteList(&a);
}
