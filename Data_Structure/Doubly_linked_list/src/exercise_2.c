/*
Author: Nidhi Goswami
Date: 26-05-2026
Description:  In the same project, create one source file main.c.  In main.c you should have the following codes to test your implementation. Initialize an empty doubly linked list pointed by p;
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include"../header/header.h"

int32_t totalTests = 0;
int32_t passedTests = 0;

#define GREEN  "\033[0;32m"
#define RED    "\033[0;31m"
#define BLUE   "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET  "\033[0m"

void printTestResult(const char *testName,int32_t expected,int32_t actual)
{
    totalTests++;

    printf("\n" BLUE "Test: %s\n" RESET,
            testName);

    printf("expected: %d\n", expected);

    printf("actual: %d\n", actual);

    if(expected == actual)
    {
        printf(GREEN "PASS\n" RESET);

        passedTests++;
    }
    else
    {
        printf(RED "FAIL\n" RESET);
    }

    printf("----------------------------------\n");
}

void runManualTestCases()
{
    struct dnode *head = NULL;

    printf(YELLOW
           "\n===== RUNNING DLL TEST CASES =====\n"
           RESET);

    d_append(&head, 10);
    d_append(&head, 20);
    d_append(&head, 30);

    printTestResult("append Count",3,d_count(head));

    d_addatbeg(&head, 5);

    printTestResult("add Beginning",4,d_count(head));

    d_addafter(head, 1, 15);

    printTestResult("add After",5,d_count(head));

    d_delete(&head, 20);

    printTestResult("delete Node",4,d_count(head));

    printf("\nfinal DLL:\n");

    d_display(head);

    printf("\n");

    printf(YELLOW"===================================\n"RESET);

    printf("total tests  : %d\n",totalTests);

    printf("passed Tests : %d\n",passedTests);

    printf("failed Tests : %d\n",totalTests - passedTests);
}

void userInputMode()
{
    struct dnode *head = NULL;

    int32_t choice;
    int32_t number;
    int32_t location;

    while(1)
    {
        printf("\n=================================\n");

        printf("     DOUBLY LINKED LIST MENU\n");

        printf("=================================\n");

        printf("1. Insert At End\n");

        printf("2. Insert At Beginning\n");

        printf("3. Insert After Location\n");

        printf("4. Delete Node\n");

        printf("5. Display DLL\n");

        printf("6. Count Nodes\n");

        printf("7. Exit\n");

        printf("\nEnter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("Enter value: ");

                scanf("%d", &number);

                d_append(&head, number);

                break;

            case 2:

                printf("Enter value: ");

                scanf("%d", &number);

                d_addatbeg(&head, number);

                break;

            case 3:

                printf("Enter location: ");

                scanf("%d", &location);

                printf("Enter value: ");

                scanf("%d", &number);

                d_addafter(head,location,number);

                break;

            case 4:

                printf("Enter value to delete: ");

                scanf("%d", &number);

                d_delete(&head, number);

                break;

            case 5:

                d_display(head);

                break;

            case 6:

                printf("Total Nodes = %d\n",
                        d_count(head));

                break;

            case 7:

                printf("Program Exited\n");

                return;

            default:

                printf("Invalid Choice\n");
        }
    }
}

void TestCase()
{
    int32_t choice;

    printf(BLUE
           "=====================================\n"
           RESET);

    printf(BLUE
           "     DOUBLY LINKED LIST SYSTEM\n"
           RESET);

    printf(BLUE
           "=====================================\n"
           RESET);

    printf("\n1. Run Manual Test Cases\n");

    printf("2. User Input Mode\n");

    printf("3. Exit\n");

    printf("\nEnter choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
        case 1:

            runManualTestCases();

            break;

        case 2:

            userInputMode();

            break;

        case 3:

            printf("Program Exited\n");

            break;

        default:

            printf("Invalid Choice\n");
    }

}
