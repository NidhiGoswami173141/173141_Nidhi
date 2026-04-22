#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<stdlib.h>
#include"module.h"
#define BUFSIZE 100
#define MAXVAL 100
#define MAXOP 100
#define NUMBER '0'

int sp = 0;
double val[MAXVAL];

char buf[BUFSIZE];
int bufp = 0;

/* push: push value onto stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i = 0, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    if (c == '-') {
        int next = getch();
        if (!isdigit(next)) {
            ungetch(next);
            return '-';
        }
        s[++i] = c = next;
    }

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}
