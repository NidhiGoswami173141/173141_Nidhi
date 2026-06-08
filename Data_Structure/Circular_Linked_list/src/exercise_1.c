/*
Author: Nidhi Goswami
Date: 25-05-2026
Desciption: 
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"../header/header.h"
typedef struct Node{
    int32_t data;
    struct Node* next;
};

struct Node* createNode_function(int data){
     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
     if(newNode == NULL){
        printf("allocation fail\n");
     }
     newNode-> data = data;
     newNode-> next = NULL;
     return newNode;
}

void insertAtBeginning(struct Node**head , int data){
     struct Node* newNode = createNode_function(data);
     if(*head == NULL){
        *head = newNode;
        (*head) -> next = newNode;
     }
     else{
        newNode -> next = (*head) -> next;
        (*head)-> next = newNode;
     }
}


void insertAtEnd(struct Node** head, int data){
     struct Node* newNode = createNode_function(data);
     if(*head == NULL){
       *head = newNode;
       (*head) -> next = newNode;
     }
     else{
        newNode -> next = (*head) -> next;
        (*head) -> next = newNode;
         *head = newNode;
     }
}

void deleteNode_fun(struct Node** head, int data)
{
    if(*head == NULL)
    {
        printf("list is empty\n");
        return;
    }

    struct Node* current = (*head)->next;
    struct Node* prev = *head;

    if(current->data == data)
    {
        if(current == *head)
        {
            free(current);
            *head = NULL;
        }
        else
        {
            (*head)->next = current->next;
            free(current);
        }

        printf("%d deleted\n", data);
        return;
    }

    prev = current;
    current = current->next;

    while(current != (*head)->next)
    {
        if(current->data == data)
        {
            if(current == *head)
            {
                prev->next = current->next;
                *head = prev;
            }
            else
            {
                prev->next = current->next;
            }

            free(current);

            printf("\n%d deleted\n", data);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("%d not found\n", data);
}


void display_fun(struct Node* head){
     struct Node* current = head;
     if(head == NULL){
       printf("list is empty\n");
       return;
     }
     do{
       printf("%d -> ", current->data);
       current = current->next;
     }
     while(current != head);
}

void CircularLinkedlistTest(){
    struct Node* head = NULL;
    insertAtBeginning(&head,1);
    insertAtEnd(&head,2);
    insertAtEnd(&head,3);
    insertAtBeginning(&head,4);

    printf("circular linked list:\n");
    display_fun(head);

    deleteNode_fun(&head,2);

    printf("circular linked list after deleting 2:\n");
    display_fun(head);
}
