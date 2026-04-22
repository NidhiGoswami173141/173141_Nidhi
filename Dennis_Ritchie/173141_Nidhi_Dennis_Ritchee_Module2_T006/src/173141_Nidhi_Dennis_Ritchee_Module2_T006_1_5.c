/*
*AIM: Write the function any(s1,s2), which returns the first location in a string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)
*Author: Nidhi Goswami 
*Created: 22/2/2026
*/

#include <stdio.h> 
#include <string.h>
#include "module.h"

#define MAKS 500

void return_location() {
    char s1[MAKS], s2[MAKS];
    int i, j, pos = -1;

    printf("Enter First String: ");
    scanf("%s", &s1);

    printf("Enter Second String: ");
    scanf("%s", &s2);

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                pos = i+1;
                break;
            }
        }
        if (pos != -1)
            break;
    }

    if (pos != -1)
        printf("First matching position: %d\n", pos);
    else
        printf("-1 (No matching characters)\n");

}

