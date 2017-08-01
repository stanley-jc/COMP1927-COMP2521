/* 
    listIteratorG.c ... Generic List Iterator implementation
    Written by Jingcheng Li
    Date: 3th April 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {
	void  *value;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct IteratorGRep {
	
    int delble;
    Node *first;
    Node *cursprev;
    Node *cursnext;
    Node *lastele;
    Node *last;

    ElmCompareFp cmpElm;
	ElmCopyFp    copyElm;
	ElmFreeFp    freeElm;    
} IteratorGRep;

//create a new list
IteratorG IteratorGNew(ElmCompareFp cmp, ElmCopyFp copy, ElmFreeFp free)
{
    struct  IteratorGRep *it;

    it = malloc(sizeof (struct IteratorGRep));
    assert(it != NULL);
    it->delble = 0;
    it->first = it->last = it->cursprev = it->cursnext = NULL;
    it->lastele = NULL;

    it->cmpElm = cmp;
    it->copyElm = copy;
    it->freeElm = free;

    return it;
}

//reset the cursor
void reset(IteratorG it)
{
    if(it->cursnext != NULL){
       	it->cursnext->prev = it->cursprev;
	}
    if(it->cursprev != NULL){
       	it->cursprev->next = it->cursnext;
	}
    it->cursprev = NULL;
    it->cursnext = it->first;
    //ensure the condition
    it->lastele = NULL;
    it->delble = 0;
}

//add a new value into the list
int add(IteratorG it, void *v)
{
    assert(it != NULL);
    Node *toins;

    //if fail to add
    if((toins = malloc(sizeof (Node))) == NULL){
	    return 0;
    }
    toins->value = it->copyElm(v);
    //when add to the first place
    if(it->cursprev == NULL){
        it->first = toins;
        toins->next = it->cursnext;
    	if(it->cursnext != NULL){
           	it->cursnext->prev = toins;
    	}
        it->cursprev = toins;
    }
    else{
        toins->next = it->cursnext;
        toins->prev = it->cursprev;
        it->cursprev->next = toins;
        if(it->cursnext != NULL){
       		 it->cursnext->prev = toins;
	    }
        it->cursprev = toins;
    }
    //ensure the condition 
    it->lastele = NULL;
    it->delble = 0;
    return 1;
}

//if has next value
int hasNext(IteratorG it)
{
    assert(it != NULL);
    it->delble = 0;
    it->lastele = NULL;
    if(it->cursnext == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

//if has previous value
int hasPrevious(IteratorG it)
{
    assert(it != NULL);
    it->delble = 0;
    it->lastele = NULL;
    if(it->cursprev == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

//return the next value and advance the cursor
void *next(IteratorG it)
{
    assert(it != NULL);
    void *toret;

    //when it's the last
    if(it->cursnext == NULL){
        //ensure the condition
        it->delble = 0;
        it->lastele = NULL;

        return NULL;
    }
    else{
        toret = it->copyElm(it->cursnext->value);
        it->lastele = it->cursnext;
        it->cursprev = it->cursnext;
        it->cursnext = it->cursnext->next;
        it->delble = 1;

        return toret;
    }
}

//return the previous value and advance the cursor
void *previous(IteratorG it)
{
    assert(it != NULL);
    void *toret;

    //when it's the first
    if(it->cursprev == NULL){
        it->delble = 0;
        it->lastele = NULL;

        return NULL;
    }
    else{
        toret = it->copyElm(it->cursprev->value);
        it->lastele = it->cursprev;
        it->cursnext = it->cursprev;
        it->cursprev = it->cursprev->prev;
        it->delble = 1;

        return toret;
    }
}

//delete the last element returned by typical functions
int delete(IteratorG it)
{
    assert (it != NULL);
    Node *todel = it->lastele;

    //cannot delete case
    if(it->delble == 0){
        return 0;
    }
    //if there is only one node
    if(todel->prev == NULL && todel->next == NULL){
        it->first = NULL;
        it->last = NULL;
        it->cursprev = it->cursnext = NULL;
    }
    //if it's the first
    else if(todel->prev == NULL){
        it->first = todel->next;
        it->cursnext = todel->next;
        it->cursprev = NULL;
        todel->next->prev = NULL;
    }
    //if it's the last
    else if(todel->next == NULL){
        it->last = todel->prev;
        it->cursprev = todel->prev;
        it->cursnext = NULL;
        todel->prev->next = NULL;
    }
    //if it's in the middle
    else{     
        todel->next->prev = todel->prev;
        todel->prev->next = todel->next;
        if(it->lastele == it->cursnext){
            it->cursnext = it->lastele->next;
        }
        else{
            it->cursprev = it->lastele->prev;
        }
    } 
    it->freeElm(todel->value);
    free(todel);
    //ensure the condition
    it->delble = 0;
    it->lastele = NULL;

    return 1;
}

//set the value of the element returned by typical functions
int set(IteratorG it, void *v)
{
    assert(it != NULL);
    //cannot set
    if(it->lastele == NULL){
        it->lastele = NULL;
        it->delble = 0;

        return 0;
    }
    //can do the operation
    else{
        it->lastele->value = it->copyElm(v);
        it->lastele = NULL;
        it->delble = 0;

        return 1;
    }
}

//find the element after the cursor matched the value
void *findNext(IteratorG it, void *v)
{
    assert(it != NULL);
    Node *poin = it->cursnext;
    void *toret;

    while(poin) {
        if(it->cmpElm(poin->value,v) == 0){
            toret = it->copyElm(poin->value);
            it->lastele = poin;
            it->cursprev = poin;
            it->cursnext = poin->next;
            it->delble = 1;

            return toret;
        }
        poin = poin->next;
    }
    //ensure the condition
    it->lastele = NULL;
    it->delble = 0;

    return NULL;
}

//find the element after the cursor matched the value
void *findPrevious(IteratorG it, void *v)
{
    assert(it != NULL);
    Node *poin = it->cursprev;
    void *toret;

    while(poin) {
        if(it->cmpElm(poin->value,v) == 0){
            toret = it->copyElm(poin->value);
            it->lastele = poin;
            it->cursnext = poin;
            it->cursprev = poin->prev;
            it->delble = 1;

            return toret;
        }
        poin = poin->prev;
    }
    //ensure the condition
    it->lastele = NULL;
    it->delble = 0;

    return NULL;
}





