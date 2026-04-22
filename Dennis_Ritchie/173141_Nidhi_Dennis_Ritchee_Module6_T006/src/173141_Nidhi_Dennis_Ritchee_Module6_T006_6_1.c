/*
Author: Nidhi Goswami
Date: 13-04-2026
Description : Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines. Write a better version.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include"module.h"
#define MAXWORD 100

// ---------- KEYWORDS ----------
struct key {
    char *word;
    int count;
};

struct key keytab[] = {
 {"auto", 0},
  {"break",0},
  {"case",0},
 {"char",0},
  {"const",0},
  {"continue",0},
  {"default",0},
  {"else",0},
  {"float",0},
 { "if",0},
  {"register",0},
  {"signed",0},
  {"struct",0},
   {"union",0},
  {"volatile",0},
  {"do",0},
  {"enum",0},
  {"for",0},
  {"int",0},
  {"return",0},
  {"sizeof",0},
  {"switch",0},
  {"unsigned",0},
  {"while",0},
  {"double",0},
  {"extern",0},
  {"goto",0},
  {"long",0},
  {"short",0},
  {"static",0},
  {"typedef",0},
  {"void",0}
};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

// ---------- FUNCTIONS ----------
static int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);

// ---------- MAIN ----------
void  getwords_ver(){
    char word[MAXWORD];
    int n;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || word[0] == '_') {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
        }
    }

    printf("\nKeyword Count:\n");
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0)
            printf("%s : %d\n", keytab[n].word, keytab[n].count);
    }

}

/////////////////////////////////////////////////////////////

// ---------- BETTER GETWORD ----------
static int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()));

    // -------- HANDLE PREPROCESSOR --------
    if (c == '#') {
        while ((c = getchar()) != '\n' && c != EOF);
        return getword(word, lim);
    }

    // -------- HANDLE COMMENTS --------
    if (c == '/') {
        int next = getchar();

        // /* comment */
        if (next == '*') {
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        }

        // // comment
        if (next == '/') {
            while ((c = getchar()) != '\n' && c != EOF);
            return getword(word, lim);
        }

        ungetc(next, stdin);
    }

    // -------- HANDLE STRINGS --------
    if (c == '"') {
        while ((c = getchar()) != '"' && c != EOF) {
            if (c == '\\') getchar(); // skip escape
        }
        return getword(word, lim);
    }

    // -------- NORMAL WORD ----------
    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        c = getchar();
        if (!isalnum(c) && c != '_') {
            ungetc(c, stdin);
            break;
        }
        *w = c;
    }

    *w = '\0';
    return word[0];
}

/////////////////////////////////////////////////////////////

// ---------- BINARY SEARCH ----------
int binsearch(char *word, struct key tab[], int n) {
    int low = 0, high = n - 1, mid, cond;

    while (low <= high) {
        mid = (low + high) / 2;
        cond = strcmp(word, tab[mid].word);

        if (cond < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

