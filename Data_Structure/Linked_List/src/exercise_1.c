/*
Author: Nidhi Goswami
Date: 12-05-2026
Description: Write a Count() function that counts the number of times a given int occurs in a list.
*/

#include<stdio.h>
#include "../header/header.h"
#include<stdint.h>
#include<stdlib.h>
int Count(struct node* head, int64_t searchFor){

     int32_t count=0;
     struct node* current = head;
     while(current != NULL){
         if(current-> data == searchFor){
             count++;
         }
         current = current->next;
     }
     return count;
}

void CountTest(){

    struct node* mylist;
    int32_t count;
    mylist = BuildOneTwoThree();
    Print(mylist);
    count = Count(mylist,2);
    printf("count:%d\n",count);

}
