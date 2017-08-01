/*
  client to test listIteratorInt.
  Written by ....
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorInt.h"


// size of line buffers
#define MAX 100

typedef struct Node {

    int value;
    struct Node *prev;
    struct Node *next;
    // implement struct here .. 

} Node;

typedef struct IteratorIntRep {
   
    int nitems;
    int delble;
    Node *first;
    Node *cursprev;
    Node *cursnext;
    Node *lastele;
    Node *last;
    // implement struct here .. 
  
} IteratorIntRep;

int getCommand();
void showList(IteratorInt it);

int main(int argc, char *argv[])
{
	// Variables used throughout main

	IteratorInt it;      // lines from input file as a DLList
	int  done;       // flag for end-of-edit-session
	int num;
	int a;
	int com;
	int *p;

	it = IteratorIntNew();
	done = 0;
	while (!done) {
		com = getCommand();
		switch (com) {
		case 1:
			scanf("%d",&num);
			a = add(it,num);
			printf("%d\n",a);
			showList(it);
			break;

		case 2:
			a = hasNext(it);
			printf("%d\n",a);
			showList(it);
			break;

		case 3:
			a = hasPrevious(it);
			printf("%d\n",a);
			showList(it);
			break;

		case 4:
			p = next(it);
			if(p == NULL){
				printf("null\n");
			}
			else{
				printf("%d\n",*p);
			}
			showList(it);
			break;

		case 5:
			p = previous(it);
			if(p == NULL){
				printf("null\n");
			}
			else{
				printf("%d\n",*p);
			}
			showList(it);
			break;

		case 6:
			reset(it);
			showList(it);
			break;

		case 7:
			a = delete(it);
			printf("%d\n", a);
			showList(it);
			break;

		case 8:
			scanf("%d",&num);
			a = set(it,num);
			printf("%d\n", a);
			showList(it);
			break;
		case 10:
			scanf("%d",&num);
			p = findNext(it,num);
			if(p == NULL){
				printf("null\n");
			}
			else{
				printf("%d\n",*p);
			}
			showList(it);
			break;

		case 11:
			scanf("%d",&num);
			p = findPrevious(it,num);
			if(p == NULL){
				printf("null\n");
			}
			else{
				printf("%d\n",*p);
			}
			showList(it);
			break;
		
		case 9:
			done = 1;
			break;
		}
	}
	
	// Finish up cleanly

	return EXIT_SUCCESS;
}

// getCommand(buf)
// prompt for and read next user command
// store it in buf
// return 1 if got a command, 0 if EOF
int getCommand()
{
	int a;
	printf("please in put\n");
	scanf("%d",&a);
	return a;
}

void showList(IteratorInt it)
{
	Node *p = it->first;
	if(it->cursprev == NULL){
			printf("^ ");
		}
	while(p){
		printf("%d ", p->value);
		if(p == it->cursprev){
			printf("^ ");
		}
		
		p = p->next;

	}
	printf("\n");

}

