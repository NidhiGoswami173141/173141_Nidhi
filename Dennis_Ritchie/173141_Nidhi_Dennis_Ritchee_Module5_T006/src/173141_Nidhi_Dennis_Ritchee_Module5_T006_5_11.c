/**
 *  This program entab and detab to accept a list of tab stops as arguments. 
 * Used the default tab settings if there are no arguments.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include"module.h"
#define MAXLINE 100 /* Maximum line size */
#define TABINC 8    /* Default tab increment size */
#define YES 1
#define NO 0

/* Function Declarations */
void esettab(int argc, char *argv[], char *tab);
void detab_fn(char *tab);
int tabpos(int pos, char *tab);

/**
 * Main function: Initializes tab stops and replaces tabs with blanks.
 */
void detab_entab(int argc, char *argv[]) {
    char tab[MAXLINE + 1];

    printf("\nTab Stop Adjustment Program\n");
    printf("----------------------------------------\n");
    printf("This program replaces tabs with spaces based on tab stop settings.\n");
    printf("You can specify custom tab stops using the format: -m +n\n");
    printf("Default behavior: Tab stops every %d columns.\n\n", TABINC);

    esettab(argc, argv, tab);
    printf("Processing input...\n\n");
    detab_fun(tab);
    printf("\nProcessing complete.\n");

    return 0;
}

/**
 * esettab: Sets tab stops based on user input or defaults.
 * @argc: Argument count.
 * @argv: Argument values.
 * @tab: Tab stop settings array.
 */
void esettab(int argc, char *argv[], char *tab) {
    int i, inc, pos;

    if (argc <= 1) {
        /* Default tab stops */
        printf("Using default tab stops every %d columns.\n", TABINC);
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = (i % TABINC == 0) ? YES : NO;
    } else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
        /* User-provided range */
        pos = atoi(&argv[1][1]);
        inc = atoi(&argv[2][1]);
        printf("Custom tab stops: Start at column %d, increment by %d.\n", pos, inc);

        for (i = 1; i <= MAXLINE; i++)
            if (i != pos)
                tab[i] = NO;
            else {
                tab[i] = YES;
                pos += inc;
            }
    } else {
        /* User-provided specific tab stops */
        printf("Custom tab stops specified individually.\n");
        for (i = 1; i <= MAXLINE; i++)
            tab[i] = NO;

        while (--argc > 0) {
            pos = atoi(*++argv);
            if (pos > 0 && pos <= MAXLINE) {
                printf("Setting tab stop at column %d.\n", pos);
                tab[pos] = YES;
            }
        }
    }
}

/**
 * detab: Replaces tabs in input with spaces based on tab stops.
 * @tab: Tab stop settings array.
 */
void detab_fun(char *tab) {
    int c, pos = 1;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            do {
                putchar(' ');
            } while (tabpos(pos++, tab) != YES);
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
}

/**
 * tabpos: Determines if a position is a tab stop.
 * @pos: Current position.
 * @tab: Tab stop settings array.
 * @return: YES if position is a tab stop, NO otherwise.
 */
int tabpos(int pos, char *tab) {
    if (pos > MAXLINE)
        return YES;
    else
        return tab[pos];
}


