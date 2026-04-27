/*
Author : Nidhi Goswami
Date : 29-3-2026
Description : As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to p>
*/
#include<stdio.h>
#include<stdint.h>
#include <ctype.h>
#include "module.h"


/*
Author : nidhi goswami
Date: 29-3-2026
Description : function for get integer
*/

int32_t getint(int32_t *pn) {
    int32_t Char, sign;
    printf("eter an integer: ");
    while (isspace(Char = getch()))
        ;

    if (!isdigit(Char) && Char != EOF && Char != '+' && Char != '-') {
        ungetch(Char);
        printf("invalid entry\n");
        return 0;
    }

    sign = (Char == '-') ? -1 : 1;

    if (Char == '+' || Char == '-') {
        int32_t next = getch();


        if (!isdigit(next)) {
            ungetch(next);
            ungetch(Char);
            printf("invalid entry\n");
            return 0;
        }
        Char = next;
    }

    for (*pn = 0; isdigit(Char); Char = getch())
        *pn = 10 * (*pn) + (Char - '0');

    *pn *= sign;

    if (Char != EOF)
        ungetch(Char);

    printf("valid Integer: %d\n", *pn);

    return (Char == EOF) ? EOF : 1;
}
