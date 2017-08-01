// listIteratorG.h ... interface to generic List Iterator
// Written by Ashesh Mahidadia, March 2017

#ifndef LISTITERATORG_H
#define LISTITERATORG_H

#include <stdio.h>

typedef struct IteratorGRep *IteratorG;

typedef int   (*ElmCompareFp)(void const *e1, void const *e2);
typedef void *(*ElmCopyFp)(void const *e1);
typedef void  (*ElmFreeFp)(void *e1);


IteratorG IteratorGNew(ElmCompareFp cmp, ElmCopyFp copy, ElmFreeFp free);
int  add(IteratorG it, void *vp);
int  hasNext(IteratorG it);
int  hasPrevious(IteratorG it);
void *next(IteratorG it);
void *previous(IteratorG it);
int  delete(IteratorG it);
int  set(IteratorG it, void *vp);
void *findNext(IteratorG it, void *vp);
void *findPrevious(IteratorG it, void *vp);
void reset(IteratorG it);

#endif
