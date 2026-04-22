/*
Author: Nidhi Goswami
Date : 19-04-2026
Description : Write a function undef that will remove a name and definition from the table maintained by lookup and install.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"module.h"
#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

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

static char *mystrdup(char *s) {
    char *p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

static struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {

        np = (struct nlist *)malloc(sizeof(*np));
        np->name = mystrdup(name);

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;

    } else {
        free(np->defn);
    }

    np->defn = mystrdup(defn);
    return np;
}

static void undef(char *name) {
    unsigned hashval = hash(name);
    struct nlist *curr = hashtab[hashval];
    struct nlist *prev = NULL;

    while (curr != NULL) {
        if (strcmp(name, curr->name) == 0) {

            if (prev == NULL)
                hashtab[hashval] = curr->next;
            else
                prev->next = curr->next;

            free(curr->name);
            free(curr->defn);
            free(curr);

            printf("Deleted successfully\n");
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    printf("Not found\n");
}

static void print_table() {
    printf("\nName\t\tDefinition\n");

    for (int i = 0; i < HASHSIZE; i++) {
        struct nlist *np = hashtab[i];

        while (np != NULL) {
            printf("%s\t\t%s\n", np->name, np->defn);
            np = np->next;
        }
    }
}

void hash_table(){

    int choice;
    char name[100], defn[100];

    while (1) {

    printf("\n1.Insert  2.Delete  3.Display  4.Exit\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("\nEOF detected. Exiting...\n");
        return;
    }
    getchar();

    switch (choice) {

    case 1:
        printf("Enter Name: ");
        if (scanf("%s", name) != 1) {
            printf("\nEOF detected. Exiting...\n");
            return;
        }

        printf("Enter Definition: ");
        if (scanf(" %[^\n]", defn) != 1) {
            printf("\nEOF detected. Exiting...\n");
            return;
        }

        install(name, defn);
        printf("Added/Updated\n");
        break;

    case 2:
        printf("Enter Name to delete: ");
        if (scanf("%s", name) != 1) {
            printf("\nEOF detected. Exiting...\n");
            return;
        }

        undef(name);
        break;

    case 3:
        print_table();
        break;

    case 4:
        return;

    default:
        printf("Invalid choice\n");
    }
  }

}

