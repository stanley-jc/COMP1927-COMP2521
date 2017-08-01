// testListIteratorG.c ... client to test Generic List Iterator 
// 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listIteratorG.h"
#include "positiveIntType.h"
#include "stringType.h" 

typedef struct Node {
	void  *value;
	struct Node *next;
	struct Node *prev;
  // implement struct here .. 

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
  // implement struct here .. 

} IteratorGRep;

int getCommand();
void showList(IteratorG it);

#define MAXARRAY 50
/*
int main(int argc, char *argv[])
{
  IteratorG it;      // lines from input file as a DLList
  int done;       // flag for end-of-edit-session
  int num;
  int a;
  int com;
  int *p;

  it = IteratorGNew(positiveIntCompare, positiveIntCopy, positiveIntFree);
  done = 0;
  while (!done) {
    com = getCommand();
    switch (com) {
    case 1:
      scanf("%d",&num);
      a = add(it,&num);
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
      p = (int *) next(it);
      if(p == NULL){
        printf("null\n");
      }
      else{
        printf("%d\n",*p);
      }
      showList(it);
      break;

    case 5:
      p =(int *) previous(it);
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
      a = set(it,&num);
      printf("%d\n", a);
      showList(it);
      break;
    case 10:
      scanf("%d",&num);
      p =(int *) findNext(it,&num);
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
      p =(int *) findPrevious(it,&num);
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

  void showList(IteratorG it)
  {
  Node *p = it->first;
  if(it->cursprev == NULL){
      printf("^ ");
    }
  while(p){
    printf("%d ", *(int*) p->value);
    if(p == it->cursprev){
      printf("^ ");
    }
    
    p = p->next;

  }
  printf("\n");

}  */
int main(int argc, char *argv[])
{
  IteratorG it;      // lines from input file as a DLList
  int done;       // flag for end-of-edit-session
  char num[MAXARRAY];
  int a;
  int com;
  char *p;

  it = IteratorGNew(stringCompare, stringCopy, stringFree);
  done = 0;
  while (!done) {
    com = getCommand();
    switch (com) {
    case 1:
      scanf("%s",num);
      printf("good\n");
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
      p = (char *) next(it);
      if(p == NULL){
        printf("null\n");
      }
      else{
        printf("%s\n",p);
      }
      showList(it);
      break;

    case 5:
      p =(char *) previous(it);
      if(p == NULL){
        printf("null\n");
      }
      else{
        printf("%s\n",p);
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
      scanf("%s",num);
      a = set(it,num);
      printf("%d\n", a);
      showList(it);
      break;
    case 10:
      scanf("%s",num);
      p =(char *) findNext(it,num);
      if(p == NULL){
        printf("null\n");
      }
      else{
        printf("%s\n",p);
      }
      showList(it);
      break;

    case 11:
      scanf("%s",num);
      p =(char *) findPrevious(it,num);
      if(p == NULL){
        printf("null\n");
      }
      else{
        printf("%s\n",p);
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

  void showList(IteratorG it)
  {
  Node *p = it->first;
  if(it->cursprev == NULL){
      printf("^ ");
    }
  while(p){
    printf("%s ", (char*) p->value);
    if(p == it->cursprev){
      printf("^ ");
    }
    
    p = p->next;

  }
  printf("\n");

}  
  /* The following code, inside the comments, may or may not be correct!
     
     It's provided in case you find it difficult to understand 
     how to create a generic list iterator, and use it's functions.
     
     Please study SetG example we discussed in the lecture in detail,
     example code is available at 
     https://www.cse.unsw.edu.au/~cs1927/16s1/lecs/week03/SetG/

     The code below only tests basic operations, however 
     make sure that you do test all the required functions properly in
     your test file. 

  */
  
  /* =======================================
     --------- positiveIntType List Iterator ----------
  */
  
/*
  IteratorG it1 = IteratorGNew(positiveIntCompare, positiveIntCopy, positiveIntFree);
  
  int a[MAXARRAY] = { 25, 12, 6, 82 , 11};
  
  int i;
  for(i=0; i<MAXARRAY; i++){
    int result = add(it1 , &a[i]); 
    printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
*/	
	/*
	The above loop should print ... 
		Inserting 25: Success 
		Inserting 12: Success 
		Inserting 6: Success 
		Inserting 82: Success 
		Inserting 11: Success
	*/  

/*
  int *v1 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v1 );  // should print "Previous value is: 11" 
  
  int *v2 = (int *) previous(it1);
  printf("Previous value is: %d \n", *v2 );  // should print "Previous value is: 82" 
  
  int *v3 = (int *) next(it1);
  printf("Next value is: %d \n", *v3 );     // should print "Next value is: 82" 
*/  

  /* =======================================
     --------- stringType List Iterator ----------
  */
 
/* 
  IteratorG it2 = IteratorGNew(stringCompare, stringCopy, stringFree);
  
  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby"); 
  
  int j;
  for(j=0; j<4; j++){
    int result = add(it2 , strA[j]); 
    printf("Inserting %s: %s \n", strA[j], (result==1 ? "Success" : "Failed") );
  }
*/
	/*
	The above loop should print ... 
		Inserting john: Success 
		Inserting rita: Success 
		Inserting john: Success 
		Inserting abby: Success
	*/
/*
  char *v4 = (char *) previous(it2);
  printf("Previous value is: %s \n", v4 );  // should print: "Previous value is: abby"
  
  char *v5 = (char *) previous(it2);
  printf("Previous value is: %s \n", v5 );  // should print: "Previous value is: john"
  
  char *v6 = (char *) next(it2);
  printf("Next value is: %s \n", v6 );      // should print: "Next value is: john"
  
*/
