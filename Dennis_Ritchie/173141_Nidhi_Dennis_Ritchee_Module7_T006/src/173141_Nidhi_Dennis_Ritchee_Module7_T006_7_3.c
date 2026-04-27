/*
Author: Nidhi Goswami
Date: 21/04/2026
Description : Revise minprintf to handle more of the other facilities of printf
*/


#include <stdio.h>
#include <stdarg.h>
#include"module.h"
void minprintf(const char *fmt, ...)
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

            default:
                putchar(*p);
                break;
        }
    }

    va_end(ap);
}

void min_printf()
{
    int iNum;
    float fNum;
    double dDoub;
    unsigned int uUnint;
    char cCharacter;
    char sStr[100];

    printf("enter integer: ");
    scanf("%d", &iNum);

    printf("enter float: ");
    scanf("%f", &fNum);

    printf("enter double: ");
    scanf("%lf", &dDoub);

    printf("enter unsigned integer: ");
    scanf("%u", &uUnint);

    printf("enter character: ");
    scanf(" %c", &cCharacter);

    printf("enter string: ");
    scanf(" %[^\n]", sStr);

    printf("\ninput:\n");

    minprintf("integer iNum: %d\n", iNum);
    minprintf("float fDnum: %f\n", fNum);
    minprintf("double dDoub: %lf\n", dDoub);
    minprintf("unsigned integer uUnint: %u\n", uUnint);
    minprintf("character cCharacter: %c\n", cCharacter);
    minprintf("string sStr: %s\n", sStr);
    minprintf("octal representation of iNum: %o\n", iNum);
    minprintf("hexadecimal representation of iNum: %x\n", iNum);
    minprintf("pointer pPointer: %p\n", (void *)&iNum);

}
