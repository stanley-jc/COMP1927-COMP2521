// tu.c ... test URL extractor
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <curl/curl.h>
#include "url.h"
#include "url_file.h"

#define BUFSIZE 1024

void normalise(char *in, char *out, int n);
void strlower(char *s);

char BASE[BUFSIZE];

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];

	if(argc > 1)
		strcpy(BASE,argv[1]);
	else {
		fprintf(stderr, "Usage: %s BaseURL\n",argv[0]);
		exit(1);
	}
		
	handle = url_fopen(BASE, "r");
	if (!handle) {
		fprintf(stderr,"couldn't url_fopen() %s\n", BASE);
		return 2;
	}
	while(!url_feof(handle)) {
		url_fgets(buffer,sizeof(buffer),handle);
		strlower(buffer);
		fputs(buffer,stdout);
		char *cur, link[BUFSIZE], full_link[BUFSIZE];
		cur = buffer;
		while ((cur = nextURL(cur)) != NULL) {
			getURL(cur, link, BUFSIZE-1);
			normalise(link, full_link, BUFSIZE-1);
			printf("%s\n",full_link);
			cur += strlen(link);
		}
	}

	url_fclose(handle);
	return 0;
}

void normalise(char *in, char *out, int n)
{
	if (strstr(in, "http") != NULL)
		strcpy(out, in);
	else if (in[0] == '/') {
		strcpy(out, BASE);
		strcat(out, in);
	}
	else {
		strcpy(out, BASE);
		strcat(out, "/");
		strcat(out, in);
	}
}

void strlower(char *s)
{
	for ( ; *s != '\0'; s++)
		*s = tolower(*s);
}
