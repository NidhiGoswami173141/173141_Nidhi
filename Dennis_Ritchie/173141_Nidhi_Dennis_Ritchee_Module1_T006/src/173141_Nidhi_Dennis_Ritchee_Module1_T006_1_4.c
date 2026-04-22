/*Author: Nidhi Goswami
Date: 10-2-2026
Description:function for print celsius to fahrenheit table 
*/

#include <stdio.h>
#include"module.h"

/* print Celsius-Fahrenheit table
   for celsius = 0, 20, ..., 300; floating-point version */

void celsius_fehrenheit()
{
    float celsius, fahr;
    float lower, upper, step;

    lower = 0;     /* lower limit of temperature scale */
    upper = 300;   /* upper limit */
    step  = 20;    /* step size */

    printf("Celsius-Fahrenheit Table\n");
    printf("Celsius\tFahrenheit\n");

    celsius = lower;
    while (celsius <= upper)
    {
        fahr = (celsius * 9.0 / 5.0) + 32.0;
        printf("%3.0f\t\t%6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

