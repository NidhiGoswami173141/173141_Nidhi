#include <stdio.h>
#include <stdint.h>
#include "module.h"

int verify_EOF()
{
    uint8_t c;
	getchar();
    	if(((c = getchar()) != EOF) == 0)
    		printf("Statement getchar() != EOF = 0\n  %hhd",c);
	else
		printf("Statement getchar() != EOF = 1\n %hhd",c);

    return 0;
}
