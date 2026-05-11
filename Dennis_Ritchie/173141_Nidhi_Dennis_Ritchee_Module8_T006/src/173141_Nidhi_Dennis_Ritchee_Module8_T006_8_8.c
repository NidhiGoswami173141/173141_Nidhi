/*
Author: Nidhi Goswami
Date : 30-04-2026
Description : Write a routine bfree(p,n) that will free any arbitrary block p of n characters into the free list maintained by malloc and free. By using bfree, a user can add a static or external array to the free list at any time.
*/

#include <unistd.h>
#include <stdio.h>
#include"module.h"
#include<stdint.h>
typedef long Align;

/* Header structure */
union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

/* free: put block ap in free list */
void free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    }

    /* join to upper neighbor */
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    /* join to lower neighbor */
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}

/* morecore: ask system for more memory */
#define NALLOC 1024

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;

    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));

    return freep;
}

/* malloc: general-purpose storage allocator */
static void *mymalloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep) {
            if ((p = morecore(nunits)) == NULL)
                return NULL;
        }
    }
}

/* bfree: add arbitrary block to free list */
void bfree(void *p, unsigned n)
{
    Header *bp;

    if (n < sizeof(Header))
        return;

    /* initialize free list if needed */
    if (freep == NULL) {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    bp = (Header *)p;
    bp->s.size = n / sizeof(Header);

    free((void *)(bp + 1));
}

void bfree_fun()
{
    static Header buffer[1000];

    int32_t number, index;

    printf("adding buffer to free list using bfree...\n");
    bfree(buffer, sizeof(buffer));

    printf("enter number of elements: ");
    scanf("%d", &number);

    int32_t *arr = (int32_t *)mymalloc(number * sizeof(int32_t));

    if (arr == NULL) {
        printf("memory allocation failed!\n");
        return;
    }

    printf("enter %d elements:\n", number);
    for (index = 0; index < number; index++) {
        scanf("%d", &arr[index]);
    }

    printf("entered element:\n");
    for (index = 0; index < number; index++) {
        printf("%d ", arr[index]);
    }
    printf("\n");

    printf("freeing memory...\n");
    free(arr);

    printf("done.\n");
}


