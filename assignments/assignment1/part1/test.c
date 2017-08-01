

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorInt.h"


// size of line buffers
#define MAX 100

int getCommand(char *s);
void showList(IteratorInt it);

int main(int argc, char *argv[])
{
	// Variables used throughout main

	IteratorInt it;      // lines from input file as a DLList
	char cmd[MAX];   // command typed by user
	int  n;          // line numbers/displacements
	int  done;       // flag for end-of-edit-session
	char new[MAX];   // buffer to hold newly inserted line
	int num;
	int a;


	it = IteratorIntNew();
	done = 0;
	while (!done && getCommand(cmd)) {
		switch (cmd[0]) {
		case 'add':
			scanf("%d",&num);
			a = add(it,num);
			printf("%d\n",a);
			showList(it);
			break;

		case 'hasNext':
			a = hasNext(it);
			printf("%d\n",a);
			showList(it);
			break;

		case 'hasPrevious':
			a = hasPrevious(it);
			printf("%d\n",a);
			showList(it);
			break;

		case 'next':
			*a = next(it);
			printf("%d\n",a);
			showList(it);
			break;

		case 'previous':
			*a = previous(it);
			printf("%d\n",a);
			showList(it);
			break;

		case 'reset':
			reset(it);
			showList(it);
			break;

		case 'delete':
			a = delete(it);
			printf("%d\n", a);
			showList(it);
			break;

		case 'set':
			scanf("%d",&num);
			a = set(it,num);
			printf("%d\n", a);
			showList(it);
			break;
		case 'q':
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
int getCommand(char *buf)
{
	printf("> ");
	return (fgets(buf, MAX, stdin) != NULL);
}

void showList(IteratorInt it)
{
	Node *p = it->first;

	while(p){
		printf("%d ", p->value);
		if(p = it->cursprev){
			printf("^ ");
		}
		p = p->next;
	}
	printf("\n");

}

