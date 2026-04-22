/*
* Write a program to check a C program for rudimentary syntax errors
* like unmatched parentheses, brackets and braces.
* Don't forget about quotes, escape sequences and comments.
* Author : Rushabh Goswami
* Modified : Nidhi Goswami
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "module.h"

#define MAXInput 1000

void check_syntax(char Input[]);

void check_C_program()
{
    char Input[MAXInput];

    printf("Enter Input (Press CTRL+D to stop) : \n");

    while (fgets(Input, MAXInput, stdin) != NULL)
    {
        check_syntax(Input);
    }
}

/*
* check_syntax : check whether given string have balanced
* parentheses, brackets and braces or not
* author : Nidhi Goswami
*/

void check_syntax(char Input[])
{
    int32_t Parentheses = 0;
    int32_t Brackets = 0;
    int32_t Braces = 0;

    bool Single_quotes = false;
    bool Double_quotes = false;

    bool Block_comment = false;
    bool Line_comment = false;

    int32_t Counter = 0;

    while (Input[Counter] != '\0')
    {

        if (Input[Counter] == '\\')
        {
            Counter += 2;
            continue;
        }

        if (Line_comment && Input[Counter] == '\n')
        {
            Line_comment = false;
        }

        if (Block_comment && Input[Counter] == '*' && Input[Counter + 1] == '/')
        {
            Block_comment = false;
            Counter += 2;
            continue;
        }

        if (!Single_quotes && !Double_quotes)
        {
            if (!Block_comment && !Line_comment &&
                Input[Counter] == '/' && Input[Counter + 1] == '*')
            {
                Block_comment = true;
                Counter += 2;
                continue;
            }

            if (!Block_comment && !Line_comment &&
                Input[Counter] == '/' && Input[Counter + 1] == '/')
            {
                Line_comment = true;
                Counter += 2;
                continue;
            }
        }

        if (Block_comment || Line_comment)
        {
            Counter++;
            continue;
        }

        if (!Double_quotes && Input[Counter] == '\'')
        {
            Single_quotes = !Single_quotes;
        }
        else if (!Single_quotes && Input[Counter] == '"')
        {
            Double_quotes = !Double_quotes;
        }

        if (!Single_quotes && !Double_quotes)
        {
            if (Input[Counter] == '(')
            {
                ++Parentheses;
            }
            else if (Input[Counter] == ')')
            {
                --Parentheses;
            }

            if (Input[Counter] == '[')
            {
                ++Brackets;
            }
            else if (Input[Counter] == ']')
            {
                --Brackets;
            }

            if (Input[Counter] == '{')
            {
                ++Braces;
            }
            else if (Input[Counter] == '}')
            {
                --Braces;
            }
        }

        Counter++;
    }

    if (Parentheses != 0)
    {
        printf("Error: Unbalanced Parentheses\n");
    }

    if (Brackets != 0)
    {
        printf("Error: Unbalanced Brackets\n");
    }

    if (Braces != 0)
    {
        printf("Error: Unbalanced Braces\n");
    }

    if (Single_quotes)
    {
        printf("Error: Unbalanced Single Quotes\n");
    }

    if (Double_quotes)
    {
        printf("Error: Unbalanced Double Quotes\n");
    }

    if (Block_comment)
    {
        printf("Error: Block comment not closed\n");
    }
}


