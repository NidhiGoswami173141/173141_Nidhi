/*
Author:Nidhi Goswami
Date : 9-03-2026
Description: Write a recursive version of the function reverse(s), which reverses the string s in place.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<string.h>
void recursive_function(char String[]) {
    int32_t len = strlen(String);

    if (len <= 1) {
        return;
    }

    char temp = String[0];
    String[0] = String[len - 1];
    String[len - 1] = '\0';
    recursive_function(String + 1);
    String[len - 1] = temp;
}

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for reverse using recursion 
*/

void recursive_reverse() {
    char String[100];
    printf("enter a string:\n");
    scanf(" %[^\n]", String);

    recursive_function(String);

    printf("Reversed: %s\n", String);
}

