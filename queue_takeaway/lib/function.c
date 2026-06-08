#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"

void PQ(LinkedListPQ *pq)
{
   pq -> front = NULL;
}

int32_t isEmpty(LinkedListPQ *pq){
    return (pq->front == NULL);
}

void clear(LinkedListPQ *pq)
{
   PTNode *temp;
   while(pq -> front != NULL){
      temp = pq->front;
      pq ->front = pq ->front ->next;
      free(temp);
   }
}


void FreePQ(LinkedListPQ *pq)
{
  clear(pq);
}


void newPT(LinkedListPQ *pq , char *name , int32_t priority)
{
   PTNode *newNode = (PTNode *)malloc(sizeof(PTNode));
   strcpy(newNode -> name, name);
   newNode -> priority = priority;
   newNode -> next = NULL;


   if(pq -> front == NULL)
   {
     pq -> front = newNode;
     return;
   }
   if(priority < pq -> front -> priority){
     newNode -> next = pq -> front;
     pq -> front = newNode;
     return;
   }
   PTNode *curr = pq -> front;
   while(curr -> next != NULL && curr-> next -> priority <= priority){
      curr = curr -> next;
   }
   newNode -> next = curr -> next;
   curr -> next = newNode;
}

char* processPT(LinkedListPQ *pq){
   if(pq->front == NULL){
     printf("queue is empty\n");
     return NULL;
   }
   PTNode *temp = pq -> front;
   char *name = (char *)malloc(strlen(temp -> name)+1);
   strcpy(name, temp-> name);
   pq -> front = temp -> next;
   free(temp);
   return name;
}

char *frontName(LinkedListPQ *pq){
    if(pq->front == NULL){
      printf("queue is empty\n");
      return NULL;
    }
    return pq -> front -> name;
}

int32_t frontPriority(LinkedListPQ *pq){
    if(pq -> front == NULL){
       printf("queue is empty\n");
       return -1;
    }
    return pq -> front -> priority;
}

void upgradePT(LinkedListPQ *pq, char *name , int32_t newPriority){
    PTNode *curr = pq->front;
    PTNode *prev = NULL;

    PTNode *target = NULL;
    PTNode *targetPrev = NULL;

    while(curr != NULL){
      if(strcmp(curr->name,name)==0){
        if(target == NULL || curr -> priority < target -> priority){
           target = curr;
           targetPrev = prev;
        }
      }
      prev = curr;
      curr = curr -> next;
    }
    if(target == NULL){
      printf("patient not found\n");
      return ;
    }
    if(newPriority >= target-> priority){
       printf("new priority must be smaller\n");
       return;
    }
    if(targetPrev == NULL){
      pq -> front = target -> next;
    }
    else{
      targetPrev -> next = target -> next;
    }
    target -> priority = newPriority;
    if(pq -> front == NULL || newPriority < pq->front->priority){
        target -> next= pq->front;
        pq -> front = target;
        return;
    }
    curr = pq -> front;
    while(curr -> next != NULL && curr -> next -> priority <= newPriority){
         curr = curr -> next;
    }
    target -> next = curr -> next;
    curr -> next = target;
}


void toString(LinkedListPQ *pq){
    PTNode * curr = pq -> front;
    printf("{");
    while(curr != NULL){
       printf("%d : %s", curr -> priority , curr -> name);
       if(curr -> next != NULL){
         printf(", ");
       }
       curr = curr->next;
    }
    printf("}\n");
}

void displayQueue(LinkedListPQ *pq)
{
    printf("\nCurrent patient queue:\n");

    toString(pq);

    if(isEmpty(pq))
        printf(" (empty)\n");
    else
        printf(" (not empty)\n");
}
