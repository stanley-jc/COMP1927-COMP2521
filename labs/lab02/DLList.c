// DLList.c - Implementation of doubly-linked list ADT
// Written by John Shepherd, March 2013
// Modified by John Shepherd, August 2014, August 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DLList.h"

// data structures representing DLList

typedef struct DLListNode {
char   *value;  // value of this list item (string)
struct DLListNode *prev;
              // pointer previous node in list
struct DLListNode *next;
              // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
int  nitems;      // count of items in list
DLListNode *first; // first node in list
DLListNode *curr;  // current node in list
DLListNode *last;  // last node in list
} DLListRep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *it)
{
DLListNode *new;
new = malloc(sizeof(DLListNode));
assert(new != NULL);
new->value = strdup(it);
new->prev = new->next = NULL;
return new;
}

// create a new empty DLList
DLList newDLList()
{
struct DLListRep *L;

L = malloc(sizeof (struct DLListRep));
assert (L != NULL);
L->nitems = 0;
L->first = NULL;
L->last = NULL;
L->curr = NULL;
return L;
}

// free up all space associated with list
void freeDLList(DLList L)
{
assert(L != NULL);
DLListNode *curr, *prev;
curr = L->first;
while (curr != NULL) {
prev = curr;
curr = curr->next;
free(prev);
}
free(L);
}

// trim off \n from strings (private function)
// this is needed for getDLList() because of fgets()
// alternatively, we could use the evil gets() function
static char *trim(char *s)
{
int end = strlen(s)-1;
if (s[end] == '\n') s[end] = '\0';
return s;
}

// create an DLList by reading items from a file
// assume that the file is open for reading
// assume one item per line, line < 999 chars
DLList getDLList(FILE *in)
{
DLList L;
DLListNode *new;
char line[1000];

L = newDLList();
while (fgets(line,1000,in) != NULL) {
char *value = strdup(trim(line));
new = newDLListNode(value);
if (L->last == NULL) {
L->first = L->last = new;
}
else {
L->last->next = new;
new->prev = L->last;
L->last = new;
}
L->nitems++;
}
L->curr = L->first;
return L;
}

// display items from a DLList, one per line
void showDLList(FILE *out, DLList L)
{
assert(out != NULL); assert(L != NULL);
DLListNode *curr;
for (curr = L->first; curr != NULL; curr = curr->next)
fprintf(out,"%s\n",curr->value);
}

// check sanity of a DLList (for testing)
int validDLList(DLList L)
{
if (L == NULL) {
fprintf(stderr,"DLList is null\n");
return 0;
}
if (L->first == NULL) {
// list is empty; curr and last should be null
if (L->last != NULL || L->curr != NULL) {
fprintf(stderr,"Non-null pointers in empty list\n");
return 0;
}
}
else {
// list is not empty; curr and last should be non-null
if (L->last == NULL || L->curr == NULL) {
fprintf(stderr,"Null pointers in non-empty list\n");
return 0;
}
}
int count;
DLListNode *curr;
// check scanning forward through list
count = 0;
for (curr = L->first; curr != NULL; curr = curr->next) {
if (curr->prev != NULL && curr->prev->next != curr) {
fprintf(stderr, "Invalid forward link into node (%s)\n",curr->value);
return 0;
}
if (curr->next != NULL && curr->next->prev != curr) {
fprintf(stderr, "Invalid backward link into node (%s)\n",curr->value);
return 0;
}
count++;
}
if (count != L->nitems) {
fprintf(stderr, "Forward count mismatch; counted=%d, nitems=%d\n",
       count, L->nitems);
return 0;
}
// check scanning backward through list
count = 0;
for (curr = L->last; curr != NULL; curr = curr->prev) {
count++;
}
if (count != L->nitems) {
fprintf(stderr, "Backward count mismatch; counted=%d, nitems=%d\n",
       count, L->nitems);
return 0;
}
// nothing went wrong => must be ok
return 1;
}

// return item at current position
char *DLListCurrent(DLList L)
{
assert(L != NULL); assert(L->curr != NULL);
return L->curr->value;
}

// move current position (+ve forward, -ve backward)
// return 1 if reach end of list during move
// if current is currently null, return 1
int DLListMove(DLList L, int n)
{
assert(L != NULL);
if (L->curr == NULL)
return 1;
else if (n > 0) {
while (n > 0 && L->curr->next != NULL) {
L->curr = L->curr->next;
n--;
}
}
else if (n < 0) {
while (n < 0 && L->curr->prev != NULL) {
L->curr = L->curr->prev;
n++;
}
}
return (L->curr == L->first || L->curr == L->last);
}

// move to specified position in list
// i'th node, assuming first node has i==1
int DLListMoveTo(DLList L, int i)
{
assert(L != NULL); assert(i > 0);
L->curr = L->first;
return DLListMove(L, i-1);
}

// insert an item before current item
// new item becomes current item
void DLListBefore(DLList L, char *it)
{
    assert(L != NULL);
    DLListNode *toins = newDLListNode(it);

    if(L->nitems == 0){
        L->first = toins;
        L->last = toins;
	toins->next = NULL;
	toins->prev = NULL;
    }
    else if(L->curr->prev == NULL){
        L->first = toins;
	toins->next = L->curr;
    	toins->prev = NULL;
        L->curr->prev = toins;
    }
    else{
	toins->next = L->curr;
    	toins->prev = L->curr->prev;
        L->curr->prev->next = toins;
        L->curr->prev = toins;
    }
    L->curr = toins;
    L->nitems++;
    printf("Added\n");
    //DLListNode
    // COMPLETE THIS FUNCTION
}

// insert an item after current item
// new item becomes current item
void DLListAfter(DLList L, char *it)
{


    // COMPLETE THIS FUNCTION*/
    assert(L != NULL);
    DLListNode *toins = newDLListNode(it);

    if(L->nitems == 0){
        L->first = toins;
        L->last = toins;
	toins->next = NULL;
	toins->prev = NULL;
    }
    else if(L->curr->next == NULL){
	toins->prev = L->curr;
	toins->next = NULL;
        L->last = toins;
        L->curr->next = toins;
    }
    else{
   	toins->prev = L->curr;
	toins->next = L->curr->next;
        L->curr->next->prev = toins;
        L->curr->next = toins;
    }
    L->curr = toins;
    L->nitems++;
    printf("Added\n");
}

// delete current item
// new item becomes item following current
// if current was last, current becomes new last
// if current was only item, current becomes null
void DLListDelete(DLList L)
{
    assert (L != NULL);
    DLListNode *todel = L->curr;

    if(L->nitems == 0){
        printf("Failed to delete...as there is nothing in the text...\n");
        return;
    }
    if(todel->prev == NULL && todel->next == NULL){
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	}
    else if(todel->prev == NULL){
        L->first = L->curr->next;
        todel->next->prev = NULL;
        free(todel->value);
        free(todel);
        L->curr = L->curr->next;
    }
    else if(todel->next == NULL){
        L->last = L->curr->prev;
        todel->prev->next = NULL;
        free(todel->value);
        free(todel);
        L->curr = L->curr->prev;
    }
    else{
        todel->next->prev = todel->prev;
        todel->prev->next = todel->next;
        free(todel->value);
        free(todel);
        L->curr = L->curr->next;
    }
    L->nitems--;
    printf("Deleted\n");
    // COMPLETE THIS FUNCTION
}

// return number of elements in a list
int DLListLength(DLList L)
{
return (L->nitems);
}

// is the list empty?
int DLListIsEmpty(DLList L)
{
return (L->nitems == 0);
}


