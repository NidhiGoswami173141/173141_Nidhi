#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#define BUFSIZE 255
int getchar_fun(void)
{
    static char buf[BUFSIZE];
    static char *bufp = NULL;
    static int  n = 0;

    if (n == 0) {
       n = read(0, buf, BUFSIZE);
       bufp = buf;
    }

    if (n > 0) {
        n -= 1;
        return *bufp++;
    } else if(n == 0){
        return EOF;

    }else{
        return -1;
    }
}
