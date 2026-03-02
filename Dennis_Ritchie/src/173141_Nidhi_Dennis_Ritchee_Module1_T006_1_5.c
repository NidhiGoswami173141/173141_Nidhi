/*Author: Nidhi Goswami
Date: 10-2-2026
Decription: function for  temperature conversion table in reverse order
*/

#include <stdio.h>
#include <stdint.h>
#include "module.h"

void reverse_tem_table()
{
 int8_t fahr;
 for (fahr = 300; fahr >= 0; fahr -=20)
 printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
