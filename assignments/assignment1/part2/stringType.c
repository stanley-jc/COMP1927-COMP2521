// stringType.c ... 
// stringType functions for generic ADT, implementation 
// Written by Ashesh Mahidadia, March 2017


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stringType.h" 

/* =====   Functions for stringType ===== */

void stringFree(void *vp){
  free(vp);
}

void *stringCopy(void const *vp){
  return strdup(vp);
}

int stringCompare(void const *vp1, void const *vp2){
  return strcmp(vp1, vp2);
}



