/*
Author: Nidhi Goswami
Date: 18-05-2026
Description: Create a program that simulates a to-do list manager using a queue. The program should allow users to perform the following operations:
Add a task to the to-do list.
If the task is already present in the list - then ignore the task
Display the current to-do list once all tasks have been added
*/

#include<stdio.h>
#include"../header/header.h"
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#define MAX 10

bool isDuplicate(int arr[], int size, int value)
{
    for (int32_t index = 0; index < size; index++)
    {
        if (arr[index] == value)
        {
            return true;
        }
    }

    return false;
}

void TodoListTest()
{
    queue* Q = queue_new();

    int32_t tasks[MAX];

    int32_t count = 0;

    int32_t value;

    printf("Enter maximum 10 tasks:\n");

    for (int32_t index = 0; index < MAX; index++)
    {
        scanf("%d", &value);

        if (!isDuplicate(tasks, count, value))
        {
            tasks[count] = value;

            count++;

            enq(Q, value);
        }
    }

    printf("\nTo-Do List:\n");

    while (!queue_empty(Q))
    {
        printf("%d\n", deq(Q));
    }
}

