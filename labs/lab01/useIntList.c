// useIntList.c - testing IntList data type

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "IntList.h"

int main(int argc, char *argv[])
{
	IntList myList, myOtherList;

	myList = getIntList(stdin);
	showIntList(myList);
	assert(IntListOK(myList));

	myOtherList = IntListSortedCopy(myList);
	printf("Sorted:\n");
	showIntList(myOtherList);
	assert(IntListOK(myOtherList));
	assert(IntListIsSorted(myOtherList));

	return 0;
}
