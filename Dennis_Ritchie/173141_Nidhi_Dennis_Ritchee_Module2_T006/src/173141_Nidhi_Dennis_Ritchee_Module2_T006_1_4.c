/*
AIM: Write an alternative version of squeeze(s1,s2) that deletes each character
in s1 that matches any character in the string s2.
Author: Nidhi Goswami
Created: 22/2/2026
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include"module.h"
#define MAKS 500

void squeeze() {
    char s1[100], s2[100];
    int i, j, k, found;

    printf("Enter first string: ");
    scanf("%s", &s1);
    getchar();
    printf("Enter characters to remove: ");
    scanf("%s", &s2);

    for (i = 0, k = 0; s1[i] != '\0'; i++) {
        found = 0;

        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            s1[k++] = s1[i];
        }
    }

    s1[k] = '\0';

    printf("Result: %s", s1);

}

