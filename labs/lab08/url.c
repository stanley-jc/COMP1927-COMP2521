// url.c ... find/extract URLs from a string
// Written by John Shepherd, September 2015

#include <string.h>

// nextURL(S)
// - finds start of next URL in string S
// - returns NULL if no (more) URLs
// - finds URLs by searching for "href"
// - assumes string has been strlower'd
char *nextURL(char *s)
{
	char *c;
	// find next "href" in string
	c = strstr(s,"href");
	if (c == NULL) return NULL;
	// skip over "href" to start of URL
	while (*c != '\0') {
		if (*c == '"' || *c == '\'') break;
		c++;
	}
	if (*c == '\0') return NULL;
	c++; // set to start of URL
	return c;
}

// getURL(S,Buf,N)
// - copies URL starting at S into Buf
// - stops copying when either
//   - reaches a ' or "
//   - reaches end of S
//   - has copied N-1 chars
// - return value indicates whether URL is complete
//   - returns 1 if stopped by ' or "
//   - returns 0 otherwise
// - appends '\0' to Buf (included in N)
int getURL(char *src, char *dest, int N)
{
	char *c = src;
	char *d = dest;
	int nc = 0;
	while (nc < N && *c != '\0') {
		if (*c == '"' || *c == '\'') break;
		*d++ = *c++;
		nc++;
	}
	*d = '\0';
	return (nc < N && *c != '\0');
}
