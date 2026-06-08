/*
Author: Nidhi Goswami
Date: 13-05-2026
Description: This is a variant on Push(). Instead of creating a new node and pushing it onto the given list, MoveNode() takes two lists, removes the front node from the second list and pushes it onto the front of the first. This turns out to be a handy utility function to have for several later problems. Both Push() and MoveNode() are designed around the feature that list operations work most naturally at the head of the list. Here's a simple example of what MoveNode() should do...
*/

#include<stdio.h>
#include<stdint.h>
#include"../header/header.h"

void MoveNode(struct node** destRef, struct node** sourceRef){

        struct node* newnode;
        newnode = *sourceRef;
        *sourceRef = newnode -> next;
        newnode -> next = *destRef;
        *destRef = newnode;

}

void MoveNodeTest(){
       struct node* a= BuildOneTwoThree();
       struct node* b = BuildOneTwoThree();
       printf("before move a and b:\n");
       Print(a);
       Print(b);
       MoveNode(&a,&b);
       printf("after move a and b:\n");
       Print(a);
       Print(b);

       DeleteList(&a);
       DeleteList(&b);
}

