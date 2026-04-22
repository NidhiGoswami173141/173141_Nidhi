/*
Author: Nidhi Goswami
Date : 6-03-2026
Description : Add access to library functions like sin, exp, and pow.
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
Description: function for  perform function like sin , exp and pow
*/

void fun_calculator()
 {
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
 case 'sin':
    push(sin(pop()*3.1415926535 / 180));
    break;
 case 'exp':
    push(exp(pop()));
    break;
 case 'pow':
    op2 = pop();
    push(pow(pop(), op2));
    break;

 case '\n':
 printf("\t%.8g\n", pop());
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
case 'c':
    sp = 0;
    break;

 default:
 printf("error: unknown command %s\n", s);
 break;
 }
 }
 }


