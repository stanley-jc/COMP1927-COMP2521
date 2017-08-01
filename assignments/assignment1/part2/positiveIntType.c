// positiveIntType.c ... 
// positiveIntType functions for generic ADT, implementation 
// Written by Ashesh Mahidadia, March 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "positiveIntType.h" 

/* =====   Functions for positiveIntType  ===== */

void positiveIntFree(void *vp){
  free(vp);
}

void *positiveIntCopy(void const *vp){
  int v = * (int *) vp ;   
  // OR use local method like int v = getInt(vp);
  
  int *ip = malloc(sizeof(int));
  *ip = v;
  return ip;
}

int positiveIntCompare(void const *vp1, void const *vp2){
  int v1 = * (int *) vp1 ;
  int v2 = * (int *) vp2 ;
  
  if( v1 == v2 ){ return 0; }
  if( v1 < v2 ) { return -1; }
  return 1;
}



