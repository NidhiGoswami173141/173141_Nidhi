/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: Write a Pop() function that is the inverse of Push(). Pop() takes a non-empty list, deletes

the head node, and returns the head node's data. If all you ever used were Push() and

Pop(), then here linked list would really look like a stack.
*/


#include<stdio.h>
#include"../header/header.h"
#include<stdlib.h>
#include<stdint.h>


struct node* BuildOnetwoThree(){

     struct node* head = NULL;
     Push(&head,3);
     Push(&head,2);
     Push(&head,1);
     return(head);

}

int Pop(struct node** headRef){

     struct node* head;
     int data;
     head = *headRef;
     data = head->data;
     *headRef = head -> next;
     free(head);
     return data;
}

void PopTest(){
     struct node* head = BuildOnetwoThree();
     int a = Pop(&head);
     int b  = Pop(&head);
     int c = Pop(&head);
     int len = Length(head);
     printf("lennth:%d\n",len);
     printf("a:%d\n",a);
     printf("b:%d\n",b);
     printf("c:%d\n",c);
     printf("%d",head);
}
