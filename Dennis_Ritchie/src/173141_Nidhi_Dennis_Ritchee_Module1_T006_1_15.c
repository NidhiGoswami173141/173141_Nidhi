/*
Author : Nidhi Goswami
Date : 18-02-2026
Description : Rewrite the temperature conversion program of Section 1.2 to use a function
for conversion.
*/

#include <stdio.h>

void convertToFahrenheit() 
{
    float fahr, celsius;

    printf("Enter temperature in Celsius: (press (CTRL + D) for exit)");

    if (scanf("%f", &celsius) == 1) {
        fahr = (celsius * (9.0 / 5.0)) + 32.0;
        printf("C = %.2f\n", celsius);
        printf("F = %.2f\n", fahr);
    } else {
        printf("Please enter valid number\n");
    }
}

