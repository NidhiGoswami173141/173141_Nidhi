/*
Author: Nidhi Goswami
Description: Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly. C comments don't nest.
Date: 12-2-2026
*/




#include<stdio.h>
#include<stdint.h>
#include"module.h"
#define MAXSIZE 20000

void remove_comments()
{
                char Char;

                char Arr[MAXSIZE];

                int32_t Index = 0;

                printf("Enter your code below to remove all the comments from it: \n ");

                while ((Char = getchar()) != EOF)
                {
                        Arr[Index++] = Char;
                }

                printf("<==================== Code without comments ====================>\n");

                int32_t Length_of_Array = Index-1;

                for(Index = 0; Index <= Length_of_Array; Index++)
                {
                        if (Arr[Index] == '\"' )
                        {
                                while(Arr[Index] != '\"')
                                        printf("%c", Arr[Index++]);
                                printf("%c", Arr[Index]);
                        }
                        else if (Arr[Index] == '/')
                        {
                                if(Arr[Index+1] == '*')
                                {
                                        while(1)
                                        {
                                                if( (Arr[Index-1] == '*') && (Arr[Index] == '/'))
                                                        break;
                                                else
                                                        Index++;
                                        }
                                }
                                else if (Arr[Index+1] == '/')
                                {
                                        while(Arr[Index] != '\n')
                                        {
                                                Index++;
                                        }
                                }

                        }
                        else
                                printf("%c", Arr[Index]);
                }
}






