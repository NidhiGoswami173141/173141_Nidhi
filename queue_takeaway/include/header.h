#ifndef MODULE_H
#define MODULE_H
#include<stdint.h>
#include<stdio.h>
typedef struct PTNode
{
    char name[100];
    int32_t priority;
    struct PTNode *next;
}PTNode;


typedef struct{
PTNode *front;
}LinkedListPQ;

void PQ(LinkedListPQ *pq);
void FreePQ(LinkedListPQ *pq);
void clear(LinkedListPQ *pq);
char* processPT(LinkedListPQ *pq);
void upgradePT(LinkedListPQ *pq, char *name , int32_t newPriority);
void linkedlist_pq();
int32_t isEmpty(LinkedListPQ *pq);
void newPT(LinkedListPQ *pq , char *name , int32_t priority);
char *frontName(LinkedListPQ *pq);
void toString(LinkedListPQ *pq);
void displayQueue(LinkedListPQ *pq);
#endif
