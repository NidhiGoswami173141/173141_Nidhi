/*
Author: Nidhi Goswami
Date : 17-4-2026
Description : Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line numbers on which it occurs. Remove noise words like ``the,'' ``and,'' and so on.
*/

#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include"module.h"
#include<string.h>
#include<ctype.h>
#define MAXWORD 100
#define MAXLINES 100

struct tnode {
    char *word;
    int count;
    int lines[MAXLINES];
    int line_count;
    struct tnode *left;
    struct tnode *right;
};

int lineno = 1;

char *noise[] = {
    "a","an","the","is","am","are","to","from","at","and","i"
};

int noise_count = sizeof(noise)/sizeof(noise[0]);

int get_word(char *, int);
struct tnode *add_tree(struct tnode *, char *, int);
void tree_print(struct tnode *);
struct tnode *t_alloc(void);
char *my_strdup(char *);
int is_noise(char *);

void cross_referntial() {
    char word[MAXWORD];
    struct tnode *root = NULL;

    while (get_word(word, MAXWORD) != EOF) {

        if (isalpha(word[0])) {

            for (int i = 0; word[i]; i++)
                word[i] = tolower(word[i]);

            if (!is_noise(word))
                root = add_tree(root, word, lineno);
        }
    }

    printf("\n---- Cross Reference Output ----\n\n");
    tree_print(root);
}

struct tnode *add_tree(struct tnode *p, char *w, int lineno) {
    int cond;

    if (p == NULL) {
        p = t_alloc();
        p->word = my_strdup(w);
        p->count = 1;
        p->lines[0] = lineno;
        p->line_count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;

        if (p->lines[p->line_count - 1] != lineno) {
            p->lines[p->line_count++] = lineno;
        }
    }
    else if (cond < 0)
        p->left = add_tree(p->left, w, lineno);
    else
        p->right = add_tree(p->right, w, lineno);

    return p;
}

void tree_print(struct tnode *p) {
    if (p != NULL) {
        tree_print(p->left);

        printf("%d: %s -> ", p->count, p->word);
        for (int i = 0; i < p->line_count; i++)
            printf("%d ", p->lines[i]);
        printf("\n");

        tree_print(p->right);
    }
}


struct tnode *t_alloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *my_strdup(char *s) {
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int is_noise(char *word) {
    for (int i = 0; i < noise_count; i++) {
        if (strcmp(word, noise[i]) == 0)
            return 1;
    }
    return 0;
}


int get_word(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getchar())) {
        if (c == '\n')
            lineno++;
    }

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
