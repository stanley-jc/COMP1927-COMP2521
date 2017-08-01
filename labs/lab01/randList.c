// randList.c - generate a list of random integers
// Written by John Shepherd, July 2008
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int max, i;

	max = (argc == 1) ? 20 : atoi(argv[1]);
	srand(time(NULL));

	for (i = 0; i < max; i++)
		printf("%d\n",1+rand()%9999);

	return 0;
}
