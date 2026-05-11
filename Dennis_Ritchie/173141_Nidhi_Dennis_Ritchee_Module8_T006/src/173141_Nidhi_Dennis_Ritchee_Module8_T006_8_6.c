/*
Author : Nidhi Goswami
Date : 29-04-2026
Description: The standard library function calloc(n,size) returns a pointer to n objects of size size, with the storage initialized to zero. Write calloc, by calling malloc or by modifying it. 
*/

#include <unistd.h>
#include <stdio.h>
#include"module.h"
#include<stdint.h>
typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;        /* empty list */
static Header *freep = NULL;

/* forward declaration */
static Header *morecore(unsigned);

void *my_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    /* calculate units needed */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {

        if (p->s.size >= nunits) {

            if (p->s.size == nunits) {
                /* exact fit */
                prevp->s.ptr = p->s.ptr;
            } else {
                /* allocate tail end */
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

void my_free(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    }

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}

#define NALLOC 1024

static Header *morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;

    my_free((void *)(up + 1));

    return freep;
}

void *my_calloc(unsigned n, unsigned size)
{
    unsigned total = n * size;

    void *ptr = my_malloc(total);
    if (ptr == NULL)
        return NULL;

    /* set all bytes to zero */
    char *p = (char *)ptr;
    for (unsigned index = 0; index < total; index++)
        p[index] = 0;

    return ptr;
}

void calloc_fun()
{
    int32_t *arr = (int32_t *)my_calloc(5, sizeof(int32_t));

    if (arr == NULL) {
        printf("Allocation failed\n");
        return 1;
    }

    printf("Values:\n");
    for (int32_t index = 0; index < 5; index++)
        printf("%d ", arr[index]);
    printf("\n");
    arr[4]=20;
    for (int32_t index = 0; index < 5; index++)
    printf("%d ", arr[index]);
    printf("\n");

    my_free(arr);

}
