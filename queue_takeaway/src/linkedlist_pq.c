#include<stdio.h>
#include<stdint.h>
#include"../include/header.h"
void linkedlist_pq()
{
    LinkedListPQ pq;

    PQ(&pq);

    char choice;
    char name[100];
    int priority;

    while(1)
    {
        displayQueue(&pq);

        printf("\n");
        printf("N)ew, F)ront, U)pgrade, P)rocess, ");
        printf("B)ulk, C)lear, Q)uit? ");

        scanf(" %c", &choice);

        switch(choice)
        {
            case 'N':
            case 'n':

                printf("Name? ");
                scanf("%s", name);

                printf("Priority? ");
                scanf("%d", &priority);

                newPT(&pq, name, priority);

                break;

            case 'F':
            case 'f':

                if(isEmpty(&pq))
                {
                    printf("Queue is empty\n");
                }
                else
                {
                    printf("Front patient : %s\n",
                           frontName(&pq));

                    printf("Priority : %d\n",
                           frontPriority(&pq));
                }

                break;

            case 'U':
            case 'u':

                printf("Name? ");
                scanf("%s", name);

                printf("New priority? ");
                scanf("%d", &priority);

                upgradePT(&pq, name, priority);

                break;

            case 'P':
            case 'p':
            {
                char *patient =
                    processPT(&pq);

                if(patient != NULL)
                {
                    printf("Processing patient: \"%s\"\n",
                           patient);

                    free(patient);
                }

                break;
            }

            case 'B':
            case 'b':
            {
                int n;
                int i;

                printf("How many patients? ");
                scanf("%d", &n);

                for(i = 0; i < n; i++)
                {
                    printf("\nPatient %d Name: ", i + 1);
                    scanf("%s", name);

                    printf("Priority: ");
                    scanf("%d", &priority);

                    newPT(&pq, name, priority);
                }

                break;
            }

            case 'C':
            case 'c':

                clear(&pq);

                printf("Queue cleared\n");

                break;

            case 'Q':
            case 'q':

                FreePQ(&pq);

                printf("Exiting...\n");

                return 0;

            default:

                printf("Invalid Choice\n");
        }
    }
}
