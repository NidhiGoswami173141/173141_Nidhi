#include<stdio.h>
#include<stdint.h>
#include "../header/header.h"

int GetNth(struct node* head, int index)
{
    struct node* current = head;

    int32_t count = 0;

    while(current != NULL)
    {
        if(count == index)
        {
            return current->data;
        }

        count++;

        current = current->next;
    }

    return -1;
}

void GetNthTest()
{
    struct node* myList = BuildOneTwoThree();

    int lastNode = GetNth(myList, 2);

    Print(myList);

    printf("value:%d\n", lastNode);
}
