/*
Author: Nidhi Goswami
Date : 3-3-2026
Decscription : Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator and provisions for negative numbers.
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
Description: function for perform modulo operation in calculator 
*/

void calculator()
 {
 int32_t type;
 double op2;
 char s[MAXOP];
 int32_t ch;

 while ((ch = getchar()) != '\n' && ch != EOF);
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
    if (op2 != 0.0) {
        double op1 = pop();
        push((int)op1 % (int)op2);
    } else
        printf("error: zero divisor\n");
    break;

 case '\n':
 printf("\t%.8g\n", pop());
 break;
 default:
 printf("error: unknown command %s\n", s);
 break;
 }
 }
 }

