/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: Write a function DeleteList() that takes a list, deallocates all of its memory and sets itshead pointer to NULL (the empty list).
*/

#include<stdio.h>
#include<stdlib.h>
#include"../header/header.h"


int DeleteList(struct node** head){
    struct node *current = *head;
    struct node* next;
    while(current != NULL){
        next = current -> next;
        free(current);
        current = next;
    }
    ChangeToNull(head);
}

void DeleteListTest(){

     struct node* mylist = BuildOneTwoThree();
     Print(mylist);
     int Delete = DeleteList(&mylist);
     Print(mylist);

}
