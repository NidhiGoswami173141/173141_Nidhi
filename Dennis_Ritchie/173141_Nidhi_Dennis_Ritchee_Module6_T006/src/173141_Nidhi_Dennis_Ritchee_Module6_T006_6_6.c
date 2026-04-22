/*
Author : Nidhi Goswami
Date : 20-04-2026
Description: Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may also find getch and ungetch helpful.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"module.h"
#define HASHSIZE 101
#define MAXLINE 200

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

static unsigned hash(char *);
static struct nlist *lookup(char *);
static struct nlist *install(char *, char *);
static char *my_strdup(char *);
static void print_table();

void define_processer() {
    char line[MAXLINE];
    char *token, *name, *defn;
    getch();
    while (1) {
        printf("\nenter define (or type exit / Ctrl+D): ");

        if (fgets(line, MAXLINE, stdin) == NULL) {
            printf("\neof detected. exiting...\n");
            break;
        }

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0)
            break;

        token = strtok(line, " \t");

        if (token && strcmp(token, "#define") == 0) {

            name = strtok(NULL, " \t");
            defn = strtok(NULL, " \t");

            if (name && defn) {

                install(name, defn);

                printf("Added/Updated: %s -> %s\n", name, defn);

            } else {
                printf("Invalid format! Use: #define NAME VALUE\n");
            }

        } else {
            printf("Ignored (not a #define)\n");
        }
    }

    printf("\nFinal Hash Table\n");
    print_table();

}

static unsigned hash(char *s) {
    unsigned hashval = 0;

    while (*s)
        hashval = *s++ + 31 * hashval;

    return hashval % HASHSIZE;
}

static struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0)
            return np;
    }
    return NULL;
}

static struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL)
            return NULL;

        np->name = my_strdup(name);
        hashval = hash(name);

        np->next = hashtab[hashval];
        hashtab[hashval] = np;

    } else {
        free(np->defn);
    }

    np->defn = my_strdup(defn);
    return np;
}

static void print_table() {

    printf("%s          %s\n", "Name", "Definition");

    for (int i = 0; i < HASHSIZE; i++) {
        struct nlist *np = hashtab[i];

        while (np != NULL) {
            printf("%-15s %-15s\n", np->name, np->defn);
            np = np->next;
        }
    }
}

static char *my_strdup(char *s) {
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

