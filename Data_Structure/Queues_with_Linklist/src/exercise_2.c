/*
Author: Nidhi Goswami
Date: 18-05-2026
Description: Assume you've got such a circular array, with a capacity of 10. Imagine that the even integer numbers from 2 to 24 are added to and removed from the queue such that numbers are added in groups of three, followed by one number being removed afterwards. For example, 2, 4, and 6 would be added, then one number removed, followed by the next three numbers being added, then one removed, and so on.
*/


#include<stdio.h>
#include"../header/header.h"
#include<stdint.h>
#define SIZE 10

typedef struct
{
    int64_t arr[SIZE];
    int64_t front;
    int64_t rear;
} CircularQueue;

void CircularEnq(CircularQueue* Q, int64_t data)
{
    if (isFull(Q))
    {
        printf("Queue Full\n");
        return;
    }

    Q->arr[Q->rear] = data;

    Q->rear = (Q->rear + 1) % SIZE;
}

int64_t CircularDeq(CircularQueue* Q)
{
    if (isEmpty(Q))
    {
        printf("Queue Empty\n");
        return -1;
    }

    int64_t data = Q->arr[Q->front];

    Q->arr[Q->front] = -1;

    Q->front = (Q->front + 1) % SIZE;

    return data;
}

void CircularDisplay(CircularQueue* Q)
{
    printf("\nFinal Queue State:\n");

    for (int32_t index = 0; index < SIZE; index++)
    {
        if (Q->arr[index] == -1)
        {
            printf("Index %d : Empty\n", index);
        }
        else
        {
            printf("Index %d : %d\n", index, Q->arr[index]);
        }
    }

    printf("\nFront = %d\n", Q->front);
    printf("Rear  = %d\n", Q->rear);
}

void initQueue(CircularQueue* Q)
{
    Q->front = 0;
    Q->rear = 0;

    for (int32_t index = 0; index < SIZE; index++)
    {
        Q->arr[index] = -1;
    }
}

int isFull(CircularQueue* Q)
{
    return ((Q->rear + 1) % SIZE) == Q->front;
}

int isEmpty(CircularQueue* Q)
{
    return Q->front == Q->rear;
}


void CircularQueue_Q2()
{
    CircularQueue Q;

    initQueue(&Q);

    int32_t num = 2;

    while (num <= 24)
    {
        for (int32_t index = 0; index < 3 && num <= 24; index++)
        {
            CircularEnq(&Q, num);

            num += 2;
        }

        CircularDeq(&Q);
    }

    CircularDisplay(&Q);
}


