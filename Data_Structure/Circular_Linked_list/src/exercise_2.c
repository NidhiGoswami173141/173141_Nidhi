/*
Author : Nidhi goswami
Date: 26-05-2026
Description: Print the sum of all even numbers stored in a circular linked list.
*/

#include<stdio.h>
#include"../header/header.h"
#include<stdlib.h>
#include<stdint.h>

typedef struct Node{
    int32_t data;
    struct Node* next;
};

void sum_of_even_number(struct Node* head)
{
    struct Node* temp;
    int32_t sum = 0;

    if(head == NULL)
    {
        printf("list is empty\n");
        return;
    }

    temp = head->next;

    do
    {
        if(temp->data % 2 == 0)
        {
            sum = sum + temp->data;
        }

        temp = temp->next;

    }while(temp != head->next);

    printf("\nsum of even numbers = %d\n", sum);
}

void SumTest(){
     struct Node* head = NULL;
     insertAtBeginning(&head, 10);
     insertAtBeginning(&head, 20);
     insertAtEnd(&head,40);
     insertAtBeginning(&head,50);
     insertAtEnd(&head,7);
     insertAtBeginning(&head,15);
     display_fun(head);
     sum_of_even_number(head);
}
