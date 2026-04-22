/*
Author : Nidhi Goswami
Date : 19-04-2026
Description : Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"module.h"
#define MAXWORD 100
#define MAXNODES 1000

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct wordfreq {
    char *word;
    int count;
};

struct wordfreq arr[MAXNODES];
int n = 0;

int getword_fun(char *, int);
struct tnode *addtree_fun(struct tnode *, char *);
void store(struct tnode *);
void sort();
void print_result();
struct tnode *talloc_fun(void);
char *my_strdup_fun(char *);

void decreasing_order_word_frequency() {
    char word[MAXWORD];
    struct tnode *root = NULL;

    while (getword_fun(word, MAXWORD) != EOF) {

        if (isalpha(word[0])) {

            for (int i = 0; word[i]; i++)
                word[i] = tolower(word[i]);

            root = addtree_fun(root, word);
        }
    }
    store(root);

    sort();

    printf("\n---- Output (Sorted by Frequency) ----\n\n");
    print_result();

}

struct tnode *addtree_fun(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc_fun();
        p->word = my_strdup_fun(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree_fun(p->left, w);
    else
        p->right = addtree_fun(p->right, w);

    return p;
}

void store(struct tnode *p) {
    if (p != NULL) {
        store(p->left);

        arr[n].word = p->word;
        arr[n].count = p->count;
        n++;

        store(p->right);
    }
}

void sort() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i].count < arr[j].count) {
                struct wordfreq temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


void print_result() {
    for (int i = 0; i < n; i++) {
        printf("%d : %s\n", arr[i].count, arr[i].word);
    }
}

struct tnode *talloc_fun(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *my_strdup_fun(char *s) {
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int getword_fun(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    }

    *w = '\0';
    return word[0];
}

