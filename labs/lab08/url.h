// url.h ... find/extract URLs from a string
// Written by John Shepherd, September 2015

#ifndef URL_H
#define URL_H

// nextURL(S)
// - finds start of next URL in string S
char *nextURL(char *s);

// getURL(S,Buf,N)
// - copies URL starting at S into Buf
int getURL(char *src, char *dest, int N);

#endif
