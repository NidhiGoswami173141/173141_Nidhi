/*
Author: Nidhi Goswami
Date : 6-3-2026
Description : Add commands for handling variables. (It's easy to provide twenty-six variables
with single-letter names.) Add a variable for the most recently printed value. 
*/


#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include"module.h"
#include<stdlib.h>
#include<ctype.h>

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for handling varibles 
*/

void variable_handling()
 {
double var[26]={0};
double last = 0.0;
int32_t varname = 0;
int32_t pastVar = 0;

 int32_t type;
 double op2;
 char s[MAXOP];
getch();
 printf("enter input:\n");
 while ((type = getop(s)) != EOF) {
 switch (type) {
 case NUMBER:
 push(atof(s));
 break;
 case '+':
 push(pop() + pop());
 break;
 case '*':
 push(pop() * pop());
break;
 case '-':
 op2 = pop();
 push(pop() - op2);
 break;
 case '/':
 op2 = pop();
 if (op2 != 0.0)
 push(pop() / op2);
 else
 printf("error: zero divisor\n");
 break;
 case '%':
 op2 = pop();
 if (op2 != 0.0)
 push(fmod(pop(), op2));
 else
 printf("error: zero divisor\n");
 break;

case '\n':
 if (sp > 0)
 {
     last = pop();
     printf("\t%.8g\n", last);
 }
 break;

case 'A': case 'B': case 'C': case 'D': case 'E':
case 'F': case 'G': case 'H': case 'I': case 'J':
case 'K': case 'L': case 'M': case 'N': case 'O':
case 'P': case 'Q': case 'R': case 'S': case 'T':
case 'U': case 'V': case 'W': case 'X': case 'Y':
case 'Z':
    push(var[type - 'A']);
    break;

case '=':
    pop();

    if (pastVar >= 'A' && pastVar <= 'Z')
    {
        double value = pop();
        var[pastVar - 'A'] = value;
        push(value);
    }
    else
        printf("error: no variable name\n");
    break;


case 'l':
 push(last);
 break;


 case 'p':
    if (sp > 0)
        printf("Top element: %.8g\n", val[sp-1]);
    else
        printf("error: stack empty\n");
    break;
case 'd':
    if (sp > 0)
        push(val[sp-1]);
    else
        printf("error: stack empty\n");
    break;
case 's':
    if (sp > 1) {
        double temp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = temp;
    }
    else
        printf("error: not enough elements\n");
    break;
case 'v':
    printf("Variables:\n");
    for(int32_t i = 0; i < 26; i++)
    {
        if(var[i] != 0)
            printf("%c = %.8g\n", 'A' + i, var[i]);
    }
    break;

case 'c':
    sp = 0;
    break;

 default:
 printf("error: unknown command %s\n", s);
 break;
 }
pastVar = type;
 }
 }

