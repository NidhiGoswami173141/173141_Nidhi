/*
Author: Nidhi Goswami
Date : 9-2-2026
Description :function for print table heading
*/

#include <stdio.h>
#include "module.h"

 /* print Fahrenheit-Celsius table
 for fahr = 0, 20, ..., 300; floating-point version */
void fehrenhit_celsius()    /*function for converting celsius to fehrenheit*/
{
 float fahr, celsius;
 float lower, upper, step;
 lower = 0; /* lower limit of temperatuire scale */
 upper = 300; /* upper limit */
 step = 20; /* step size */
 printf("Fehrenheit-Celsius Table\n");
 printf("Fehrenheit\tCelsius\n");
 fahr = lower;
 while (fahr <= upper) {
 celsius = (5.0/9.0) * (fahr-32.0);
 printf("%3.0f\t\t%6.1f\n", fahr, celsius);
 fahr = fahr + step;
 }
}
