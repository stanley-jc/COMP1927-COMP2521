// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

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

void showCurrLine(DLList);
void showState(DLList lines);

int main(int argc, char *argv[])
{
	//DLList myList;
	DLList empList;

	// myList = getDLList(stdin);
	empList = newDLList();
	//assert(validDLList(myList));
	assert(validDLList(empList));

	printf("Hi I'm Jarvis, this is an automatic test program :)\n");
	// printf("Initial state of the text:\n");
	//showState(myList);
	printf("\nTest started.....\n");

	printf("===========================================================================\n");
	printf("Test 2: Test if DLListBefore works.....\n");
	printf("Let's start at the very beginning, a very good place to start.\n");
	printf("Test 2.1: Add the first line to an empty list......\n");
	showState(empList);
	printf("Line to be added: When you learn you begin with ABC\n");
	DLListBefore(empList,"When you learn you begin with ABC");
	showState(empList);
	assert(validDLList(empList));

	printf("Test 2.2: Add another line to an list with one line......\n");
	showState(empList);
	printf("Line to be added: When you code you begin with HelloWorld\n");
	DLListBefore(empList,"When you code you begin with HelloWorld");
	showState(empList);
	assert(validDLList(empList));

	printf("Test 2.3: Add another line before the first line of a list with some lines......\n");
	showState(empList);
	printf("Line to be added: HelloWorld, the first two words just happen to be\n");
	DLListBefore(empList,"HelloWorld, the first two words just happen to be");
	showState(empList);
	assert(validDLList(empList));

	printf("Test 2.4: Add another line to the middle of a list with some lines......\n");
	DLListMove(empList,1);
	showState(empList);
	printf("Line to be added: H-e-l-l-o-W-o-r-l-d\n");
	DLListBefore(empList,"H-e-l-l-o-W-o-r-l-d");
	showState(empList);
	assert(validDLList(empList));
	printf("Test 2 passed XD\n\n");

	printf("===========================================================================\n");
	printf("Test 3: Test if DLListDelete works.....\n");
	printf("Now we gonna delete those texts.....\n");
	printf("Test 3.1: Delete the first line of the list......\n");
	DLListMoveTo(empList, 1);
	showState(empList);
	DLListDelete(empList);
	showState(empList);
	assert(validDLList(empList));

	printf("Test 3.2: Delete the middle line of the list.......\n");
	DLListMove(empList,1);
	showState(empList);
	DLListDelete(empList);
	showState(empList);
	assert(validDLList(empList));

	printf("Test 3.3: Delete the last line of the list.......\n");
	DLListMoveTo(empList, DLListLength(empList));
	showState(empList);
	DLListDelete(empList);
	showState(empList);
	assert(validDLList(empList));

	printf("Test 3.4: Delete the last line of the list with one line.......\n");
	showState(empList);
	DLListDelete(empList);
	showState(empList);
	assert(validDLList(empList));

	printf("Test 3.5: Delete a line when the list is empty.......\n");
	showState(empList);
	DLListDelete(empList);
	showState(empList);
	assert(validDLList(empList));
	printf("Test 3 passed XD\n\n");

	printf("===========================================================================\n");
	printf("Test 4: Test if DLListAfter works.....\n");
	printf("Now we need to start at the very beginning again\n");

	printf("Test 4.1: Add the first line to an empty list......\n");
	showState(empList);
	printf("Line to be added: When you learn you begin with ABC\n");
	DLListAfter(empList,"When you learn you begin with ABC");
	showState(empList);
	assert(validDLList(empList));

	printf("Test 4.2: Add another line to an list with one line......\n");
	showState(empList);
	printf("Line to be added: When you code you begin with HelloWorld\n");
	DLListAfter(empList,"When you code you begin with HelloWorld");
	showState(empList);
	assert(validDLList(empList));

	printf("Test 4.3: Add another line to the middle of a list with some lines......\n");
	DLListMove(empList,1);
	showState(empList);
	printf("Line to be added: HelloWorld, the first two words just happen to be\n");
	DLListAfter(empList,"HelloWorld, the first two words just happen to be");
	showState(empList);
	assert(validDLList(empList));

	printf("Test 4.4: Add another line after the last line of a list with some lines......\n");
	DLListMoveTo(empList, DLListLength(empList));
	showState(empList);
	printf("Line to be added: H-e-l-l-o-W-o-r-l-d\n");
	DLListAfter(empList,"H-e-l-l-o-W-o-r-l-d");
	showState(empList);
	assert(validDLList(empList));
	printf("Test 4 passed XD\n\n");

	printf("===========================================================================\n");
	printf("A tests passed, mission accomplished.\n");
	printf("When you know the words to code, you can code most anything\n\n");
	return 0;
}

void showCurrLine(DLList L)
{
	if(L->curr != NULL){
		printf("%s\n",L->curr->value);
	}
	else{
		printf("The text is empty, so there is no current line. :(\n");
	}
}

void showState(DLList L)
{	
	printf("\n");
	printf("---------------------------------------------------------------------------\n");
	printf("Content of the text:\n");
	if(L->nitems != 0){
		showDLList(stdout,L);
		printf("\n");
	}
	else{
		printf("The text is empty, so there is nothing. :(\n");
		printf("\n");
	}
	printf("Current line:\n");
	showCurrLine(L);
	printf("\n");
	printf("Number of lines:\n");
	printf("%d\n", DLListLength(L));
	printf("---------------------------------------------------------------------------\n");
	printf("\n");
}
