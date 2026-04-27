#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define ITER 2000000

int isUpperSpace(char c)
{
    return (c >= 'A' && c <= 'Z');
}


int isUpperTime(char c)
{
    return isupper(c);
}

double measure(int (*func)(char), char ch, int *dummy)
{
    clock_t start, end;

    start = clock();

    for (int i = 0; i < ITER; i++)
    {
        *dummy += func(ch);
    }

    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

void space_time()
{
    char ch = 'A';
    int dummy = 0;

    double spaceTime = measure(isUpperSpace, ch, &dummy);
    double timeTime  = measure(isUpperTime, ch, &dummy);

    printf("Space-efficient time: %f seconds\n", spaceTime);
    printf("Time-efficient time: %f seconds\n", timeTime);

    printf("Dummy value: %d\n", dummy);

    return 0;
}
