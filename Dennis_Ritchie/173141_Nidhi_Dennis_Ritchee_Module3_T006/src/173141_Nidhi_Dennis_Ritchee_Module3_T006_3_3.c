/*
Author : Nidhi Goswami
Date: 25-02-2026
Description: Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
*/


#include <stdio.h>
#include<stdint.h>
#include"module.h"
#define Maxsize 1000

/*
Author : Nidhi Goswami
Date: 25-02-2026
Description : function for expand character and digit 
*/

void expand(char ip[], char op[]) {
   int32_t index = 0, sec_index = 0;

    printf("enter input:\n");
    scanf("%s",ip);
    while (ip[index] != '\0' && ip[index] != '\n') {

        if (ip[index] != '-' &&
            ip[index+1] == '-' &&
            ip[index+2] != '\0' &&
            ip[index+2] != '\n') {

            char start = ip[index];
            char end   = ip[index+2];

            if ((start >= 'a' && start <= 'z' && end >= 'a' && end <= 'z') ||
                (start >= 'A' && start <= 'Z' && end >= 'A' && end <= 'Z') ||
                (start >= '0' && start <= '9' && end >= '0' && end <= '9')) {

                if (start <= end) {
                    for (char Char = start; Char <= end; Char++)
                        op[sec_index++] = Char;
                } else {
                    for (char Char = start; Char >= end; Char--)
                        op[sec_index++] = Char;
                }

                index += 3;
                continue;
            }
        }

        if (ip[index] == '-' &&
            (ip == 0 || ip[index+1] == '\n' || ip[index+1] == '\0')) {
            op[sec_index++] = '-';
        }
         else if (ip[index] != '-') {
            op[sec_index++] = ip[index];
        }

        index++;
    }

    op[sec_index] = '\0';

    printf("output:\n%s\n", op);
}
