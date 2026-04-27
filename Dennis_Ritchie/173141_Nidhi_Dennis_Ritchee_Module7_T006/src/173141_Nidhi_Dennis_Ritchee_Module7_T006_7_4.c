/*
Author: Nidhi Goswami
Date : 21-04-2026
Description : Write a private version of scanf analogous to minprintf from the previous section
*/


#include <stdio.h>
#include <stdarg.h>
#include"module.h"
static void minprintf(const char *fmt, ...)
{
    va_list ap;
    const char *p;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {

        if (*p != '%') {
            putchar(*p);
            continue;
        }

        p++;

        switch (*p) {

            case 'd': {
                int val = va_arg(ap, int);
                printf("%d", val);
                break;
            }

            case 'u': {
                unsigned int val = va_arg(ap, unsigned int);
                printf("%u", val);
                break;
            }

            case 'f': {
                double val = va_arg(ap, double);
                printf("%f", val);
                break;
            }

            case 's': {
                char *val = va_arg(ap, char *);
                printf("%s", val);
                break;
            }

            case 'c': {
                int val = va_arg(ap, int);
                printf("%c", val);
                break;
            }

            case 'p': {
                void *val = va_arg(ap, void *);
                printf("%p", val);
                break;
            }

            case 'o': {
                int val = va_arg(ap, int);
                printf("%o", val);
                break;
            }

            case 'x': {
                int val = va_arg(ap, int);
                printf("%x", val);
                break;
            }

            case 'l': {
                p++;
                if (*p == 'd') {
                    long val = va_arg(ap, long);
                    printf("%ld", val);
                }
                else if (*p == 'u') {
                    unsigned long val = va_arg(ap, unsigned long);
                    printf("%lu", val);
                }
                else if (*p == 'f') {
                    double val = va_arg(ap, double);
                    printf("%lf", val);
                }
                break;
            }
        }
    }

    va_end(ap);
}

void minscanf(const char *fmt, ...)
{
    va_list ap;
    const char *p;

    va_start(ap, fmt);

    for (p = fmt; *p; p++) {

        if (*p != '%')
            continue;

        p++;

        switch (*p) {

            case 'd': {
                int *ip = va_arg(ap, int *);
                scanf("%d", ip);
                break;
            }

            case 'u': {
                unsigned int *up = va_arg(ap, unsigned int *);
                scanf("%u", up);
                break;
            }

            case 'f': {
                float *fp = va_arg(ap, float *);
                scanf("%f", fp);
                break;
            }

            case 's': {
                char *sp = va_arg(ap, char *);
                scanf(" %[^\n]", sp);
                break;
            }

            case 'c': {
                char *cp = va_arg(ap, char *);
                scanf(" %c", cp);
                break;
            }

            case 'l': {
                p++;
                if (*p == 'f') {
                    double *dp = va_arg(ap, double *);
                    scanf("%lf", dp);
                }
                break;
            }
        }
    }

    va_end(ap);
}

void min_scanf()
{
    int iNum;
    float fNum;
    double dDoub;
    unsigned int uUnint;
    char cCharacter;
    char sStr[100];

    printf("Enter integer: ");
    minscanf("%d", &iNum);

    printf("Enter float: ");
    minscanf("%f", &fNum);

    printf("Enter double: ");
    minscanf("%lf", &dDoub);

    printf("Enter unsigned integer: ");
    minscanf("%u", &uUnint);

    printf("Enter character: ");
    minscanf("%c", &cCharacter);

    printf("Enter string: ");
    minscanf("%s", sStr);

    printf("\nYou have entered:\n");

    minprintf("Integer iNum: %d\n", iNum);
    minprintf("Float fDnum: %f\n", fNum);
    minprintf("Double dDoub: %lf\n", dDoub);
    minprintf("Unsigned integer uUnint: %u\n", uUnint);
    minprintf("Character cCharacter: %c\n", cCharacter);
    minprintf("String sStr: %s\n", sStr);
    minprintf("Octal representation of iNum: %o\n", iNum);
    minprintf("Hexadecimal representation of iNum: %x\n", iNum);
    minprintf("Pointer pPointer: %p\n", (void *)&iNum);

}

